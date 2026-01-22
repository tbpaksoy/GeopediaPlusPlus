#include "shader.h"

#include <fstream>
#include <algorithm>
#include <map>
#include <string>
#include <iostream>

std::vector<std::string> structNames;
std::map<std::string, std::map<std::string, UniformType>> structMembers;
;

void RecordStructName(std::string line)
{
    if (line.find("struct ") != std::string::npos)
    {
        int begin = line.find("struct ") + 7,
            end = line.find("{", begin);

        if (begin > end)
            return;

        std::string name = line.substr(begin, end - begin);

        while (name.size() && *name.begin() == ' ')
            name.erase(0);
        while (name.size() && *(name.end() - 1) == ' ')
            name.erase(name.size() - 1);

        structNames.push_back(name);
    }
}

void RecordStructMembers(std::string structName, std::string body)
{

    while (body.find("  ") != std::string::npos)
        body.replace(body.find("  "), 2, " ");
    while (body.find("\n ") != std::string::npos)
        body.replace(body.find("\n "), 2, "\n");
    while (body.find(" \n") != std::string::npos)
        body.replace(body.find(" \n"), 2, "\n");
    while (body.find("\n\n") != std::string::npos)
        body.replace(body.find("\n\n"), 2, "\n");
    while (body.find(" ;") != std::string::npos)
        body.replace(body.find(" ;"), 2, ";");

    int begin = body.find("struct " + structName) + 7 + structName.size(),
        end = body.find("};", begin) - 1;
    if (begin > end)
        return;
    std::string structBody = body.substr(begin, end - begin);
    structBody = structBody.substr(structBody.find("{") + 1);
    while (structBody.find("\n") != std::string::npos && structBody.find(";") != std::string::npos)
    {
        int begin = structBody.find("\n") + 1,
            end = structBody.find(";", begin);
        if (begin > end)
            break;
        std::string line = structBody.substr(begin, end - begin);
        while (line.size() && *line.begin() == ' ')
            line.erase(0);
        while (line.size() && *(line.end() - 1) == ' ')
            line.erase(line.size() - 1);
        std::string typeString = line.substr(0, line.find(" "));
        UniformType type = typeString == "bool" ? b : typeString == "int" ? i
                                                  : typeString == "float" ? f
                                                  : typeString == "vec2"  ? f2
                                                  : typeString == "vec3"  ? f3
                                                  : typeString == "vec4"  ? f4
                                                                          : n;
        std::string name = line.substr(line.find(" ") + 1);
        structMembers[structName][name] = type;
        structBody = structBody.substr(end);
    }
}

bool IsStruct(std::string line)
{
    for (std::string name : structNames)
    {
        if (line.find(name + " ") != std::string::npos)
            return true;
    }
    return false;
}

std::vector<UniformMeta> MetaAnalysis(std::string code)
{

    std::vector<UniformMeta> uniformMetas;

    std::string toScan = code;
    std::map<std::string, int> prepropcessors;
    while (toScan.find("#define ") != std::string::npos)
    {
        int begin = toScan.find("#define ") + 8,
            end = toScan.find("\n", begin);

        if (begin > end)
            break;

        std::string temp = toScan.substr(begin, end - begin);

        while (temp.size() && *temp.begin() == ' ')
            temp.erase(0);
        while (temp.size() && *(temp.end() - 1) == ' ')
            temp.erase(temp.size() - 1);
        temp.erase(
            std::unique(temp.begin(), temp.end(), [](char a, char b)
                        { return a == ' ' && b == ' '; }));
        prepropcessors[temp.substr(0, temp.find(" "))] = std::stoi(temp.substr(temp.find(" ") + 1).c_str());

        toScan = toScan.substr(end);
    }

    toScan = code;
    while (toScan.find("struct ") != std::string::npos)
    {
        int begin = toScan.find("struct ") + 7,
            end = toScan.find("}", begin);

        if (begin > end)
            break;

        std::string temp = toScan.substr(begin, end - begin);

        RecordStructName("struct " + temp + "}");
        RecordStructMembers(temp.substr(0, temp.find("{") - 1), toScan);
        toScan = toScan.substr(end);
    }

    toScan = code;
    while (toScan.find("uniform ") != std::string::npos)
    {
        int begin = toScan.find("uniform ") + 8,
            end = toScan.find(";", begin);

        if (begin > end)
            break;

        std::string temp = toScan.substr(begin, end - begin);

        while (temp.size() && *temp.begin() == ' ')
            temp.erase(0);
        while (temp.size() && *(temp.end() - 1) == ' ')
            temp.erase(temp.size() - 1);
        temp.erase(
            std::unique(temp.begin(), temp.end(), [](char a, char b)
                        { return a == ' ' && b == ' '; }));

        int arrayCount = 0;
        if (temp.find("[") != std::string::npos)
        {
            size_t check = temp.find("[ ");
            if (check != std::string::npos)
                temp.erase(check + 1);
            check = temp.find(" ]");
            if (check != std::string::npos)
                temp.erase(check);

            int bracketBegin = temp.find("[") + 1,
                bracketEnd = temp.find("]");
            const char *inside = temp.substr(bracketBegin, bracketEnd - bracketBegin).c_str();
            if (prepropcessors.find(inside) != prepropcessors.end())
            {
                arrayCount = prepropcessors[inside];
                temp.replace(temp.find(inside), strlen(inside), std::to_string(arrayCount));
            }
            else if (std::all_of(inside, inside + strlen(inside), [](char c)
                                 { return std::isdigit(c); }))
                arrayCount = std::stoi(inside);
        }
        std::string typeString = temp.substr(0, temp.find(" "));
        UniformType type = typeString == "bool" ? b : typeString == "int"                                 ? i
                                                  : typeString == "float"                                 ? f
                                                  : typeString == "vec2"                                  ? f2
                                                  : typeString == "vec3"                                  ? f3
                                                  : typeString == "vec4"                                  ? f4
                                                  : structMembers.find(typeString) != structMembers.end() ? st
                                                                                                          : n;
        if (arrayCount)
        {
            if (type == st)
            {
                for (int i = 0; i < arrayCount; i++)
                {
                    std::string nameStr = temp.substr(temp.find(" ") + 1, temp.find("[") - temp.find(" "));
                    std::string indexStr = std::to_string(i) + "]";
                    for (auto member : structMembers[typeString])
                    {
                        char *name = (char *)malloc(strlen(indexStr.c_str()) + strlen(nameStr.c_str()));
                        strcpy(name, (nameStr + indexStr + "." + member.first).c_str());
                        UniformMeta meta{name, member.second};
                        uniformMetas.push_back(meta);
                    }
                }
            }
            else
                for (int i = 0; i < arrayCount; i++)
                {
                    std::string nameStr = temp.substr(temp.find(" ") + 1, temp.find("[") - temp.find(" "));
                    std::string indexStr = std::to_string(i) + "]";
                    char *name = (char *)malloc(strlen(indexStr.c_str()) + strlen(nameStr.c_str()));
                    strcpy(name, (nameStr + indexStr).c_str());
                    UniformMeta meta{name, type};
                    uniformMetas.push_back(meta);
                }
        }
        else
        {
            std::string s = temp.substr(temp.find(" ") + 1);
            char *name = (char *)malloc(strlen(s.c_str()));
            strcpy(name, s.c_str());
            UniformMeta meta{name, type};
            uniformMetas.push_back(meta);
        }
        toScan = toScan.substr(end);
    }

    return uniformMetas;
}

void CreateUniformMap(const std::vector<UniformMeta> &uniformMetas, UniformMap &uniformMap)
{
    for (UniformMeta m : uniformMetas)
    {
        std::string name(m.name);
        switch (m.type)
        {
        case b:
            uniformMap[name] = false;
            break;
        case i:
            uniformMap[name] = 0;
            break;
        case f:
            uniformMap[name] = 0.0f;
            break;
        case f2:
            uniformMap[name] = glm::vec2(0.0f);
            break;
        case f3:
            uniformMap[name] = glm::vec3(0.0f);
            break;
        case f4:
            uniformMap[name] = glm::vec4(0.0f);
            break;
        case m3:
            uniformMap[name] = glm::mat3(1.0f);
            break;
        case m4:
            uniformMap[name] = glm::mat4(1.0f);
            break;
        }
    }
}

Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
    structNames.clear();

    std::string vertexCode;
    std::string fragmentCode;

    std::ifstream vShaderFile(vertexPath);
    std::ifstream fShaderFile(fragmentPath);

    if (!vShaderFile.is_open())
        throw std::runtime_error("Failed to open vertex shader file: " + vertexPath);
    if (!fShaderFile.is_open())
        throw std::runtime_error("Failed to open fragment shader file: " + fragmentPath);

    std::string line;
    while (std::getline(vShaderFile, line))
    {
        for (int i = 0, offset = 0; i < line.size(); i++)
            if (line[i] == ';')
                line.insert(i + 1 + offset++, "\n");
        vertexCode += line + "\n";
    }
    for (UniformMeta m : MetaAnalysis(vertexCode))
        uniformMetas.push_back(m);
    while (std::getline(fShaderFile, line))
    {
        for (int i = 0, offset = 0; i < line.size(); i++)
            if (line[i] == ';')
                line.insert(i + 1 + offset++, "\n");
        fragmentCode += line + "\n";
    }
    for (UniformMeta m : MetaAnalysis(fragmentCode))
        uniformMetas.push_back(m);

    CreateUniformMap(uniformMetas, uniformMap);

    vShaderFile.close();
    fShaderFile.close();

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);
    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        throw std::runtime_error("Vertex shader compilation failed: " + std::string(infoLog));
    }
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        throw std::runtime_error("Fragment shader compilation failed: " + std::string(infoLog));
    }
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        throw std::runtime_error("Shader program linking failed: " + std::string(infoLog));
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(program);
}

void Shader::Use()
{
    glUseProgram(program);
}

void Shader::Set(const char *name, float value)
{
    glUniform1f(glGetUniformLocation(program, name), value);
}

void Shader::Set(const char *name, int value)
{
    glUniform1i(glGetUniformLocation(program, name), value);
}

void Shader::Set(const char *name, const glm::vec2 &value)
{
    glUniform2fv(glGetUniformLocation(program, name), 1, &value[0]);
}

void Shader::Set(const char *name, const glm::vec3 &value)
{
    glUniform3fv(glGetUniformLocation(program, name), 1, &value[0]);
}

void Shader::Set(const char *name, const glm::vec4 &value)
{
    glUniform4fv(glGetUniformLocation(program, name), 1, &value[0]);
}

void Shader::Set(const char *name, const glm::mat3 &value)
{
    glUniformMatrix3fv(glGetUniformLocation(program, name), 1, GL_FALSE, &value[0][0]);
}

void Shader::Set(const char *name, const glm::mat4 &value)
{
    glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, &value[0][0]);
}

void Shader::ActivateAttributeAndPointer(const char *name, GLint size, GLsizei stride, const void *pointer)
{
    GLuint attrib = glGetAttribLocation(program, name);
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, size, GL_FLOAT, GL_FALSE, stride, pointer);
}

void Shader::ActivateAttributeAndPointer(GLuint attrib, GLint size, GLsizei stride, const void *pointer)
{
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), pointer);
}

GLuint Shader::GetProgram() const
{
    return program;
}

GLuint Shader::GetVertexShader() const
{
    return vertexShader;
}

GLuint Shader::GetFragmentShader() const
{
    return fragmentShader;
}

#ifdef IMGUI
bool Shader::DrawGUI()
{
    bool result = false;
    ImGui::Text("Shader Program ID: %u", program);
    ImGui::Text("Vertex Shader ID: %u", vertexShader);
    ImGui::Text("Fragment Shader ID: %u", fragmentShader);

    for (UniformMeta m : uniformMetas)
    {
        std::string name(m.name);
        ImGui::Text("Uniform: %s", m.name);
        switch (m.type)
        {
        case b:
        {
            bool boolValue = std::get<bool>(uniformMap[name]);
            if (ImGui::Checkbox(m.name, &boolValue))
            {
                uniformMap[name] = boolValue;
                Set(m.name, boolValue);
                result = true;
            }
        }
        break;
        case i:
        {
            int intValue = std::get<int>(uniformMap[name]);
            if (ImGui::InputInt(m.name, &intValue))
            {
                uniformMap[m.name] = intValue;
                Set(m.name, intValue);
                result = true;
            }
        }
        break;
        case f:
        {
            float floatValue = std::get<float>(uniformMap[name]);
            if (ImGui::InputFloat(m.name, &floatValue))
            {
                uniformMap[m.name] = floatValue;
                Set(m.name, floatValue);
                result = true;
            }
        }
        break;
        case f2:
        {
            glm::vec2 vec2Value = std::get<glm::vec2>(uniformMap[name]);
            if (ImGui::InputFloat2(m.name, &vec2Value[0]))
            {
                uniformMap[m.name] = vec2Value;
                Set(m.name, vec2Value);
                result = true;
            }
        }
        break;
        case f3:
        {
            glm::vec3 vec3Value = std::get<glm::vec3>(uniformMap[name]);
            if (ImGui::InputFloat3(m.name, &vec3Value[0]))
            {
                uniformMap[m.name] = vec3Value;
                Set(m.name, vec3Value);
                result = true;
            }
        }
        break;
        case f4:
        {
            glm::vec4 vec4Value = std::get<glm::vec4>(uniformMap[name]);
            if (ImGui::InputFloat4(m.name, &vec4Value[0]))
            {
                uniformMap[m.name] = vec4Value;
                Set(m.name, vec4Value);
                result = true;
            }
        }
        break;
        }
    }

    return result;
}
#endif