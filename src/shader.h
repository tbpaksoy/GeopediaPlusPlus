#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>

class Shader
{
private:
    GLuint program;
    GLuint vertexShader;
    GLuint fragmentShader;
public:
    Shader(std::string vertexPath, std::string fragmentPath);
    ~Shader();

    void Use();
    void Set( const char* name, float value );
    void Set( const char* name, int value );
    void Set( const char* name, const glm::vec2& value );
    void Set( const char* name, const glm::vec3& value );
    void Set( const char* name, const glm::vec4& value );
    void Set( const char* name, const glm::mat3& value );
    void Set( const char* name, const glm::mat4& value );

    void ActivateAttributeAndPointer( const char* name, GLint size, GLsizei stride, const void* pointer);
    void ActivateAttributeAndPointer( GLuint attrib, GLint size, GLsizei stride, const void* pointer);

    GLuint GetProgram() const;
    GLuint GetVertexShader() const;
    GLuint GetFragmentShader() const;
};

#endif