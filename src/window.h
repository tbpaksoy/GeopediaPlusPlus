#ifndef WINDOW_H
#define WINDOW_H

#include "camera3d.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <functional>

class Window
{
private:
    GLFWwindow *window;
    glm::ivec2 size;
    std::string title;
    std::function<void(float)> updateCallback;
    std::function<void(int, int, int)> mouseButtonCallback;
    float lastFrameTime;

public:
    Window(glm::ivec2 size, const std::string &title);
    ~Window();

    glm::ivec2 Size() const;
    glm::ivec2 Position() const;

    glm::vec2 CursorPosition() const;

    glm::vec3 ScreenToWorldRayPerspective(const Camera3D &camera) const;
    glm::vec3 ScreenToWorldRayOrthographic(const Camera3D &camera) const;

    void SetSize(glm::ivec2 size);
    void SetPosition(glm::ivec2 position);
    void SetTitle(const std::string &title);

    void SetMouseButtonCallback(const std::function<void(int, int, int)> &callback);
    void SetUpdateCallback(const std::function<void(float)> &callback);

    void Run();
    void ForceClose();
};

#endif