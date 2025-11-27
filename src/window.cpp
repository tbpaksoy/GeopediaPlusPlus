#include "window.h"

#include <stdexcept>

#include <GL/glew.h>

#ifdef IMGUI
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include <imgui.h>
#endif

Window::Window(glm::ivec2 size, const std::string &title)
{
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    this->size = size;
    this->title = title;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
    glfwSetWindowUserPointer(window, this);

    if (!window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Failed to initialize GLEW");
    }

    glfwMakeContextCurrent(window);

#ifdef IMGUI
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();
#endif
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

glm::vec2 Window::CursorPosition() const
{
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return glm::vec2(static_cast<float>(x), static_cast<float>(y));
}

glm::vec3 Window::ScreenToWorldRayPerspective(const Camera3D &camera) const
{
    glm::vec2 cursorPos = CursorPosition();
    glm::ivec2 windowSize = Size();

    glm::vec2 ndc = glm::vec2(
        (2.0f * cursorPos.x) / windowSize.x - 1.0f,
        1.0f - (2.0f * cursorPos.y) / windowSize.y);

    glm::vec4 clipNear = glm::vec4(ndc, -1.0f, 1.0f),
              clipFar = glm::vec4(ndc, 1.0f, 1.0f);

    glm::mat4 invProjection = glm::inverse(camera.GetPerspectiveMatrix()),
              invView = glm::inverse(camera.GetViewMatrix());

    glm::vec4 viewNear = invProjection * clipNear;
    viewNear /= viewNear.w;
    glm::vec3 worldNear = glm::vec3(invView * viewNear);

    glm::vec4 viewFar = invProjection * clipFar;
    viewFar /= viewFar.w;
    glm::vec3 worldFar = glm::vec3(invView * viewFar);

    glm::vec3 direction = worldFar - worldNear;

    return glm::normalize(direction);
}
glm::vec3 Window::ScreenToWorldRayOrthographic(const Camera3D &camera) const
{
    glm::vec2 cursorPos = CursorPosition();
    glm::ivec2 windowSize = Size();

    glm::vec2 ndc = glm::vec2(
        (2.0f * cursorPos.x) / windowSize.x - 1.0f,
        1.0f - (2.0f * cursorPos.y) / windowSize.y);

    glm::vec4 clip = glm::vec4(ndc, 0.0f, 1.0f);
    glm::mat4 invProjection = glm::inverse(camera.GetOrthographicMatrix()),
              invView = glm::inverse(camera.GetViewMatrix());

    glm::vec4 world = invView * (invProjection * clip);

    glm::vec3 origin = glm::vec3(world),
              direction = glm::normalize(camera.Front());

    return direction;
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
void Window::SetTitle(const std::string &title)
{
    this->title = std::string(title.begin(), title.end());
    glfwSetWindowTitle(window, this->title.c_str());
}

void Window::Run()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();

        float currentFrameTime = glfwGetTime();
        float deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;
        if (updateCallback)
            updateCallback(deltaTime);
    }
}
void Window::ForceClose()
{
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Window::SetUpdateCallback(const std::function<void(float)> &callback)
{
    updateCallback = callback;
}
void Window::SetMouseButtonCallback(const std::function<void(int, int, int)> &callback)
{
    mouseButtonCallback = callback;
    glfwSetMouseButtonCallback(window,
                               [](GLFWwindow *win, int button, int action, int mods)
                               {
                                   Window *windowInstance = static_cast<Window *>(glfwGetWindowUserPointer(win));
                                   if (windowInstance)
                                   {
                                       windowInstance->mouseButtonCallback(button, action, mods);
                                   }
                               });
}