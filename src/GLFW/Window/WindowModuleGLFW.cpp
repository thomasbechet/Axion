#include <GLFW/Window/WindowModuleGLFW.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Context/ContextModule.hpp>
#include <Core/Renderer/RendererModule.hpp>
#include <Core/Input/InputModule.hpp>
#include <GLFW/Window/WrapperWindowModuleGLFW.hpp>

#include <GLFW/glfw3.h>

using namespace ax;

void WindowModuleGLFW::initialize() noexcept
{
    if(!glfwInit())
        Engine::interrupt("Failed to init glfw library");

    unsigned size_x = Engine::context().config.getUnsigned("Window", "default_width", 854);
    unsigned size_y = Engine::context().config.getUnsigned("Window", "default_height", 480);
    std::string title = Engine::context().config.getString("Window", "default_title", "AxionEngine");
    std::string mode = Engine::context().config.getString("Window", "default_mode", "windowed");

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
    glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_TRUE);

    m_window = glfwCreateWindow(m_size.x, m_size.y, m_title.c_str(), nullptr, nullptr);
    if(!m_window) Engine::interrupt("Failed to create window");

    if(Engine::context().config.getString("Window", "default_position_x", "default") != "default")
        m_position.x = Engine::context().config.getUnsigned("Window", "default_position_x", 50);
    else
        glfwGetWindowPos(m_window, (int*)&m_position.x, nullptr);

    if(Engine::context().config.getString("Window", "default_position_y", "default") != "default")
        m_position.y = Engine::context().config.getUnsigned("Window", "default_position_y", 50);
    else
        glfwGetWindowPos(m_window, nullptr, (int*)&m_position.y);

    m_verticalSync = Engine::context().config.getBoolean("Window", "vertical_synchronization", true);

    setMode(m_mode);
    setPosition(m_position);
    setVerticalSync(m_verticalSync);

    WrapperWindowModuleGLFW::setWindow(this, m_window);
}
void WindowModuleGLFW::terminate() noexcept
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}
void WindowModuleGLFW::update() noexcept
{
    glfwPollEvents();
}

void WindowModuleGLFW::swapBuffers() noexcept
{
    glfwSwapInterval(m_verticalSync);
    glfwSwapBuffers(m_window);
}

bool WindowModuleGLFW::requestGLContext() noexcept
{
    glfwMakeContextCurrent(m_window);
    return true;
}
bool WindowModuleGLFW::requestDXContext() noexcept
{
    return false;
}
bool WindowModuleGLFW::requestVKContext() noexcept
{
    return false;
}

bool WindowModuleGLFW::shouldClose() noexcept
{
    return glfwWindowShouldClose(m_window);
}

void WindowModuleGLFW::setTitle(std::string title) noexcept
{
    m_title = title;
    glfwSetWindowTitle(m_window, m_title.c_str());
}
std::string WindowModuleGLFW::getTitle() const noexcept
{
    return m_title;
}
void WindowModuleGLFW::setSize(Vector2u size) noexcept
{
    if(m_mode == WindowMode::Windowed)
    {
        m_size = size;
        glfwSetWindowSize(m_window, m_size.x, m_size.y);
    }
}
Vector2u WindowModuleGLFW::getSize() const noexcept
{
    if(m_mode == WindowMode::Windowed) return m_size;

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    return Vector2u(mode->width, mode->height);
}
void WindowModuleGLFW::setPosition(Vector2i position) noexcept
{
    m_position = position;
    if(m_mode == WindowMode::Windowed) glfwSetWindowPos(m_window, m_position.x, m_position.y);
}
Vector2i WindowModuleGLFW::getPosition() const noexcept
{
    return m_position;
}
void WindowModuleGLFW::setMode(WindowMode mode) noexcept
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
WindowMode WindowModuleGLFW::getMode() noexcept
{
    return m_mode;
}
void WindowModuleGLFW::setVerticalSync(bool toggle) noexcept
{
    m_verticalSync = toggle;
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(m_verticalSync);
}
bool WindowModuleGLFW::getVerticalSync() const noexcept
{
    return m_verticalSync;
}

GLFWwindow* WindowModuleGLFW::rawWindow() const noexcept
{
    return m_window;
}

void WindowModuleGLFW::windowPosCallback(int xpos, int ypos) noexcept
{
    if(m_mode == WindowMode::Windowed) m_position = Vector2i(xpos, ypos);
}
void WindowModuleGLFW::windowSizeCallback(int width, int height) noexcept
{
    if(m_mode == WindowMode::Windowed) m_size = Vector2u(width, height);
}