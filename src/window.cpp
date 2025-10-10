#include "window.h"

#include <stdexcept>

#include <GL/glew.h>


Window::Window(glm::ivec2 size, const std::string& title)
{
    if(!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    this->size = size;
    this->title = title;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr); 

    if(!window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window);


    if(glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Failed to initialize GLEW");
    }

    glfwMakeContextCurrent(window);
}
Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

glm::ivec2 Window::Size() const
{
    return size;
}
glm::ivec2 Window::Position() const
{
    int x, y;
    glfwGetWindowPos(window, &x, &y);
    return glm::ivec2(x, y);
}

void Window::SetSize(glm::ivec2 size)
{
    this->size = size;
    glfwSetWindowSize(window, size.x, size.y);
}
void Window::SetPosition(glm::ivec2 position)
{
    glfwSetWindowPos(window, position.x, position.y);
}
void Window::SetTitle(const std::string& title)
{
    this->title = std::string(title.begin(), title.end());
    glfwSetWindowTitle(window, this->title.c_str());
}

void Window::Run()
{
    while(!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();

        float currentFrameTime = glfwGetTime();
        float deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;
        if(updateCallback)
            updateCallback(deltaTime);
    }
}
void Window::ForceClose()
{
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Window::SetUpdateCallback(const std::function<void(float)>& callback)
{
    updateCallback = callback;
}