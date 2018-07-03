#include <AxionGLFW/Window/WindowGLFW.hpp>

using namespace ax;

void WindowGLFW::initialize() noexcept
{
    if(!glfwInit())
        Game::interrupt("Failed to init glfw library");

    unsigned size_x = Game::engine().config().getUnsigned("Window", "default_width", 854);
    unsigned size_y = Game::engine().config().getUnsigned("Window", "default_height", 480);
    std::string title = Game::engine().config().getString("Window", "default_title", "AxionEngine");
    std::string mode = Game::engine().config().getString("Window", "default_mode", "windowed");

    m_size = Vector2u(size_x, size_y);
    m_title = title;
    switch(mode)
    {
        case "fullscreen": m_mode = WindowMode::Fullscreen; break;
        case "windowed": m_mode = WindowMode::Windowed; break;
        case "borderless": m_mode = WindowMode::Borderless; break;
    }
}
void WindowGLFW::terminate() noexcept
{

}

void WindowGLFW::swapBuffers() noexcept
{
    glfwSwapBuffers(m_window);
}

bool WindowGLFW::requestGLContext() noexcept
{
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
    glfwSetWindowTitle(m_window, m_title);
}
std::string WindowGLFW::getTitle() const noexcept
{
    return m_title;
}
void WindowGLFW::setSize(Vector2u size) noexcept
{
    if(m_mode == WindowMode::Fullscreen) return;

    m_size = size;

}
Vector2u WindowGLFW::getSize() const noexcept
{

}
void setMode(WindowMode mode) noexcept
{
    m_mode = mode;
}
WindowMode getMode() noexcept
{
    return m_mode;
}

GLFWwindow* WindowGLFW::rawWindow() const noexcept
{
    return m_window;
}