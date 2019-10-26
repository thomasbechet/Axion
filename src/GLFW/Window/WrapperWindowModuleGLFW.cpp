#include <GLFW/Window/WrapperWindowModuleGLFW.hpp>

#include <GLFW/glfw3.h>

using namespace ax;

WindowModuleGLFW* WrapperWindowModuleGLFW::m_window = nullptr;

void WrapperWindowModuleGLFW::setWindow(WindowModuleGLFW* window, GLFWwindow* w)
{
    m_window = window;
    glfwSetWindowPosCallback(w, window_pos_callback);
    glfwSetWindowSizeCallback(w, window_size_callback);
}

void WrapperWindowModuleGLFW::window_pos_callback(GLFWwindow* window, int xpos, int ypos)
{
    m_window->windowPosCallback(xpos, ypos);
}
void WrapperWindowModuleGLFW::window_size_callback(GLFWwindow* window, int width, int height)
{
    m_window->windowSizeCallback(width, height);
}