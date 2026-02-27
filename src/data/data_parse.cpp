#include "data_parse.h"
#include <iostream>

std::map<std::string, std::string> ExtractData(const rapidcsv::Document &doc, std::vector<std::string> excludedRows, std::vector<std::string> excludedColumns)
{
        std::vector<std::string> keys = doc.GetColumnNames(), rows = doc.GetColumn<std::string>(0);
        std::map<std::string, std::string> data;
        for (int i = 1; i < doc.GetColumnCount(); i++)
        {
                if (std::find(excludedColumns.begin(), excludedColumns.end(), keys[i]) != excludedColumns.end())
                        continue;
                for (int j = 1; j < doc.GetRowCount(); j++)
                {
                        if (std::find(excludedRows.begin(), excludedRows.end(), rows[j]) != excludedRows.end())
                                continue;
                        data[rows[j] + "/" + keys[i]] = doc.GetCell<std::string>(i, j);
                }
        }
        return data;
}
std::map<std::string, std::string> ExtractData(const simdjson::dom::element &json, const std::string &keyPath, const std::map<std::string, std::string> &keyMap)
{
        std::map<std::string, std::string> data;
        if (keyMap.size() == 0 || keyMap.size() == 0 || keyPath.find("@root") == std::string::npos)
                return data;
        std::vector<std::string> keys;
        std::string path = keyPath.substr(0, keyPath.find("@root")), rest = keyPath.substr(keyPath.find("@root") + 5);
        simdjson::dom::element root;
        if (path.size() > 0)
                root = json[path];
        else
                root = json;
        if (root.is_array() && keyPath.find("@element") != std::string::npos)
        {
                std::string elementPath = keyPath.substr(keyPath.find("@element/") + 9);

                for (auto element : root.get_array())
                {
                        std::string key(element[elementPath].get_c_str());
                        keys.push_back(key);
                }
        }
        else if (root.is_object())
        {
                for (auto element : root.get_object())
                {
                        if (rest.size())
                        {
                                std::string key(element.value[rest].get_c_str());
                                keys.push_back(key);
                        }
                        else
                        {
                                std::string key(element.key);
                                keys.push_back(key);
                        }
                }
        }

        if (json.is_array())
        {
                simdjson::dom::array arr = json.get_array();
                for (auto key : keyMap)
                {
                        std::string elementPath = std::string(key.second.c_str());
                        elementPath.replace(elementPath.find("@element/"), 9, "");
                        elementPath.replace(elementPath.find("@root/"), 6, "");
                        for (int i = 0; i < arr.size(); i++)
                        {
                                std::string value;

                                if (arr.at(i).at_key(elementPath).is_string())
                                        value = std::string(arr.at(i).at_key(elementPath).get_string().value());
                                else if (arr.at(i).at_key(elementPath).is_int64())
                                        value = std::to_string((int)arr.at(i).at_key(elementPath).get_int64());
                                else if (arr.at(i).at_key(elementPath).is_double())
                                        value = std::to_string((float)arr.at(i).at_key(elementPath).get_double());
                                else if (arr.at(i).at_key(elementPath).is_bool())
                                        value = arr.at(i).at_key(elementPath).get_bool() ? "true" : "false";
                                data[keys[i] + "/" + key.first] = value;
                        }
                }
        }
        else if (json.is_object())
        {
                simdjson::dom::object obj = json.get_object();
                for (auto key : keyMap)
                {
                        if (key.second.find("@element") == std::string::npos)
                                continue;
                        std::string elementPath = std::string(key.second.c_str());
                        elementPath.replace(elementPath.find("@root/"), 6, "");
                        elementPath.replace(elementPath.find("@element/"), 9, "");
                        for (auto element : obj)
                        {
                                std::string value;

                                if (element.value[elementPath].is_string())
                                        value = std::string(element.value[elementPath].get_string().value());
                                else if (element.value[elementPath].is_int64())
                                        value = std::to_string((int)element.value[elementPath].get_int64());
                                else if (element.value[elementPath].is_double())
                                        value = std::to_string((float)element.value[elementPath].get_double());
                                else if (element.value[elementPath].is_bool())
                                        value = element.value[elementPath].get_bool() ? "true" : "false";
                                data[std::string(element.key) + "/" + key.first] = value;
                        }
                }
        }

        return data;
}
