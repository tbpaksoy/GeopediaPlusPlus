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
    std::function<void(int, int, int, int)> keyButtonCallback;
    std::function<void(double, double)> scrollCallback;
    std::function<void(int, int)> setWindowSizeCallback;
    float lastFrameTime;
    int msaa = 0;

public:
    Window(glm::ivec2 size, const std::string &title);
    Window(glm::ivec2 size, const std::string &title, int msaa);
    ~Window();

    glm::ivec2 Size() const;
    glm::ivec2 Position() const;

    glm::vec2 CursorPosition() const;

    glm::vec3 ScreenToWorldRayPerspective(const Camera3D &camera) const;
    glm::vec3 ScreenToWorldRayOrthographic(const Camera3D &camera) const;

    void SetSize(glm::ivec2 size);
    void SetAspectRatio(glm::ivec2 ratio);
    void SetPosition(glm::ivec2 position);
    void SetTitle(const std::string &title);

    void SetUpdateCallback(const std::function<void(float)> &callback);
    void SetMouseButtonCallback(const std::function<void(int, int, int)> &callback);
    void SetKeyCallback(const std::function<void(int, int, int, int)> &callback);
    void SetScrollCallback(const std::function<void(double, double)> &callback);
    void SetWindowSizeCallback(const std::function<void(int, int)> &callback);

    void Run();
    void ForceClose();

    void SetBlending(bool enabled);

    int GetMouseButtonState(int button) const;
    int GetKeyState(int key) const;
};

#endif