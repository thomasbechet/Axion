#include <GLFW/Window/WindowGLFW.hpp>

#include <Core/Context/Game.hpp>
#include <Core/Context/GameContext.hpp>
#include <Core/Renderer/Renderer.hpp>

#include <GLFW/glfw3.h>

#include <iostream>

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

    if(mode == "fullscreen")
        m_mode = WindowMode::Fullscreen;
    else if(mode == "windowed")
        m_mode = WindowMode::Windowed;
    else if(mode == "borderless")
        m_mode = WindowMode::Borderless;

    switch(m_mode)
    {
        case WindowMode::Fullscreen:
            m_window = glfwCreateWindow(m_size.x, m_size.y, m_title.c_str(), glfwGetPrimaryMonitor(), nullptr);
        break;
        case WindowMode::Windowed:
            m_window = glfwCreateWindow(m_size.x, m_size.y, m_title.c_str(), nullptr, nullptr);
        break;
        case WindowMode::Borderless:
            const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
            glfwWindowHint(GLFW_RED_BITS, mode->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
            glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

            m_window = glfwCreateWindow(mode->width, mode->height, m_title.c_str(), glfwGetPrimaryMonitor(), nullptr);
        break;
    }

    if(!m_window) Game::interrupt("Failed to create window");
}
void WindowGLFW::terminate() noexcept
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
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
    }
}
Vector2u WindowGLFW::getSize() const noexcept
{
    return m_size;
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
            Game::renderer().updateViewport();
        }
        break;
        case WindowMode::Windowed:
        {
            glfwSetWindowMonitor(m_window, nullptr, 0, 0, m_size.x, m_size.y, 0);
            Game::renderer().updateViewport();
        }
        break;
        case WindowMode::Borderless:
        {
            Game::renderer().updateViewport();
        }  
        break;
    }
}
WindowMode WindowGLFW::getMode() noexcept
{
    return m_mode;
}

GLFWwindow* WindowGLFW::rawWindow() const noexcept
{
    return m_window;
}