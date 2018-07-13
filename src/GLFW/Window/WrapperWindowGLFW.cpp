#include <GLFW/Window/WrapperWindowGLFW.hpp>

#include <GLFW/glfw3.h>

using namespace ax;

WindowGLFW* WrapperWindowGLFW::m_window = nullptr;

void WrapperWindowGLFW::setWindow(WindowGLFW* window, GLFWwindow* w)
{
    m_window = window;
    glfwSetWindowPosCallback(w, window_pos_callback);
    glfwSetWindowSizeCallback(w, window_size_callback);
}

void WrapperWindowGLFW::window_pos_callback(GLFWwindow* window, int xpos, int ypos)
{
    m_window->windowPosCallback(xpos, ypos);
}
void WrapperWindowGLFW::window_size_callback(GLFWwindow* window, int width, int height)
{
    m_window->windowSizeCallback(width, height);
}