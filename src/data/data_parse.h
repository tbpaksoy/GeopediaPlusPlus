#ifndef DATA_PARSE_H
#define DATA_PARSE_H

#include <string>
#include <vector>
#include <map>
#include <variant>

#include <simdjson.h>
#include <rapidcsv.h>
#include <tinyxml2.h>

std::map<std::string, std::string> ExtractData(const rapidcsv::Document &doc, std::vector<std::string> excludedRows = {}, std::vector<std::string> excludedColumns = {});
std::map<std::string, std::string> ExtractData(const simdjson::dom::element &json, const std::string &keyPath, const std::map<std::string, std::string> &keyMap);
#endif