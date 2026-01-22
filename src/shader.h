#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <map>
#include <variant>

#ifdef IMGUI
#include <imgui.h>
#endif

enum UniformType
{
    n,    // none - in case of error
    b,    // bool
    i,    // int
    i2,   // ivec2
    i3,   // ivec3
    i4,   // ivec4
    f,    // float
    f2,   // vec2
    f3,   // vec3
    f4,   // vec4
    sp2d, // sampler2D
    m3,   // mat3
    m4,   // mat4
    st    // struct
};

struct UniformMeta
{
    char *name;
    UniformType type;
};

typedef std::variant<bool, int, float, glm::vec2, glm::vec3, glm::vec4, glm::mat3, glm::mat4> UniformValue;
typedef std::map<std::string, UniformValue> UniformMap;

class Shader
{
private:
    GLuint program;
    GLuint vertexShader;
    GLuint fragmentShader;
    std::vector<UniformMeta> uniformMetas;
    UniformMap uniformMap;

public:
    Shader(std::string vertexPath, std::string fragmentPath);
    ~Shader();

    void Use();
    void Set(const char *name, float value);
    void Set(const char *name, int value);
    void Set(const char *name, const glm::vec2 &value);
    void Set(const char *name, const glm::vec3 &value);
    void Set(const char *name, const glm::vec4 &value);
    void Set(const char *name, const glm::mat3 &value);
    void Set(const char *name, const glm::mat4 &value);

    void ActivateAttributeAndPointer(const char *name, GLint size, GLsizei stride, const void *pointer);
    void ActivateAttributeAndPointer(GLuint attrib, GLint size, GLsizei stride, const void *pointer);

    GLuint GetProgram() const;
    GLuint GetVertexShader() const;
    GLuint GetFragmentShader() const;

#ifdef IMGUI
    bool DrawGUI();
#endif
};

#endif