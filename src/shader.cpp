#include "shader.h"

#include <fstream>

Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
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
        vertexCode += line + "\n";
    while (std::getline(fShaderFile, line))
        fragmentCode += line + "\n";
    
    vShaderFile.close();
    fShaderFile.close();

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);
    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        throw std::runtime_error("Vertex shader compilation failed: " + std::string(infoLog
        ));
    }
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        throw std::runtime_error("Fragment shader compilation failed: " + std::string(infoLog
        ));
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
        throw std::runtime_error("Shader program linking failed: " + std::string(infoLog
        ));
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

void Shader::Set( const char* name, float value )
{
    glUniform1f( glGetUniformLocation(program, name), value );
}

void Shader::Set( const char* name, int value )
{
    glUniform1i( glGetUniformLocation(program, name), value );
}

void Shader::Set( const char* name, const glm::vec2& value )
{
    glUniform2fv( glGetUniformLocation(program, name), 1, &value[0] );
}

void Shader::Set( const char* name, const glm::vec3& value )
{
    glUniform3fv( glGetUniformLocation(program, name), 1, &value[0] );
}

void Shader::Set( const char* name, const glm::vec4& value )
{
    glUniform4fv( glGetUniformLocation(program, name), 1, &value[0] );
}

void Shader::Set( const char* name, const glm::mat3& value )
{
    glUniformMatrix3fv( glGetUniformLocation(program, name), 1, GL_FALSE, &value[0][0] );
}

void Shader::Set( const char* name, const glm::mat4& value )
{
    glUniformMatrix4fv( glGetUniformLocation(program, name), 1, GL_FALSE, &value[0][0] );
}

void Shader::ActivateAttributeAndPointer( const char* name, GLint size, GLsizei stride, const void* pointer)
{
    GLuint attrib = glGetAttribLocation(program, name);
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, size, GL_FLOAT, GL_FALSE, stride, pointer);
}

void Shader::ActivateAttributeAndPointer( GLuint attrib, GLint size, GLsizei stride, const void* pointer)
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

