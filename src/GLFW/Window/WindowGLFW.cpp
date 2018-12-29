#include <GLFW/Window/WindowGLFW.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Context/EngineContext.hpp>
#include <Core/Renderer/Renderer.hpp>
#include <Core/Input/Input.hpp>
#include <GLFW/Window/WrapperWindowGLFW.hpp>

#include <GLFW/glfw3.h>

using namespace ax;

void WindowGLFW::initialize() noexcept
{
    if(!glfwInit())
        Engine::interrupt("Failed to init glfw library");

    unsigned size_x = Engine::context().config().getUnsigned("Window", "default_width", 854);
    unsigned size_y = Engine::context().config().getUnsigned("Window", "default_height", 480);
    std::string title = Engine::context().config().getString("Window", "default_title", "AxionEngine");
    std::string mode = Engine::context().config().getString("Window", "default_mode", "windowed");

    m_size = Vector2u(size_x, size_y);
    m_title = title;

    if(mode == "fullscreen")
        m_mode = WindowMode::Fullscreen;
    else if(mode == "windowed")
        m_mode = WindowMode::Windowed;
    else if(mode == "borderless")
        m_mode = WindowMode::Borderless;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_SAMPLES, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_size.x, m_size.y, m_title.c_str(), nullptr, nullptr);
    if(!m_window) Engine::interrupt("Failed to create window");

    if(Engine::context().config().getString("Window", "default_position_x", "default") != "default")
        m_position.x = Engine::context().config().getUnsigned("Window", "default_position_x", 50);
    else
        glfwGetWindowPos(m_window, (int*)&m_position.x, nullptr);

    if(Engine::context().config().getString("Window", "default_position_y", "default") != "default")
        m_position.y = Engine::context().config().getUnsigned("Window", "default_position_y", 50);
    else
        glfwGetWindowPos(m_window, nullptr, (int*)&m_position.y);

    m_verticalSync = Engine::context().config().getBoolean("Window", "vertical_synchronization", true);

    setMode(m_mode);
    setPosition(m_position);
    setVerticalSync(m_verticalSync);

    WrapperWindowGLFW::setWindow(this, m_window);
}
void WindowGLFW::terminate() noexcept
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}
void WindowGLFW::update() noexcept
{
    glfwPollEvents();
}

void WindowGLFW::swapBuffers() noexcept
{
    glfwSwapBuffers(m_window);
}

bool WindowGLFW::requestGLContext() noexcept
{
    glfwMakeContextCurrent(m_window);
    return true;
}
bool WindowGLFW::requestDXContext() noexcept
{
    return false;
}
bool WindowGLFW::requestVKContext() noexcept
{
    return false;
}

bool WindowGLFW::shouldClose() noexcept
{
    return glfwWindowShouldClose(m_window);
}

void WindowGLFW::setTitle(std::string title) noexcept
{
    m_title = title;
    glfwSetWindowTitle(m_window, m_title.c_str());
}
std::string WindowGLFW::getTitle() const noexcept
{
    return m_title;
}
void WindowGLFW::setSize(Vector2u size) noexcept
{
    if(m_mode == WindowMode::Windowed)
    {
        m_size = size;
        glfwSetWindowSize(m_window, m_size.x, m_size.y);
    }
}
Vector2u WindowGLFW::getSize() const noexcept
{
    if(m_mode == WindowMode::Windowed) return m_size;

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    return Vector2u(mode->width, mode->height);
}
void WindowGLFW::setPosition(Vector2i position) noexcept
{
    m_position = position;
    if(m_mode == WindowMode::Windowed) glfwSetWindowPos(m_window, m_position.x, m_position.y);
}
Vector2i WindowGLFW::getPosition() const noexcept
{
    return m_position;
}
void WindowGLFW::setMode(WindowMode mode) noexcept
{
    m_mode = mode;

    switch(m_mode)
    {
        case WindowMode::Fullscreen:
        {
            const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
            glfwSetWindowMonitor(m_window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, 0);
        }
        break;
        case WindowMode::Windowed:
        {
            glfwSetWindowMonitor(m_window, nullptr, m_position.x, m_position.y, m_size.x, m_size.y, 0);
        }
        break;
        case WindowMode::Borderless:
        {
            const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
            glfwWindowHint(GLFW_RED_BITS, mode->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
            glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
            glfwSetWindowMonitor(m_window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
        }  
        break;
    }
}
WindowMode WindowGLFW::getMode() noexcept
{
    return m_mode;
}
void WindowGLFW::setVerticalSync(bool toggle) noexcept
{
    m_verticalSync = toggle;
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(m_verticalSync);
}
bool WindowGLFW::getVerticalSync() const noexcept
{
    return m_verticalSync;
}

GLFWwindow* WindowGLFW::rawWindow() const noexcept
{
    return m_window;
}

void WindowGLFW::windowPosCallback(int xpos, int ypos) noexcept
{
    if(m_mode == WindowMode::Windowed) m_position = Vector2i(xpos, ypos);
}
void WindowGLFW::windowSizeCallback(int width, int height) noexcept
{
    if(m_mode == WindowMode::Windowed) m_size = Vector2u(width, height);
}