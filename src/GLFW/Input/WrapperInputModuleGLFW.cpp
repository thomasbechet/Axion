#include <GLFW/Input/WrapperInputModuleGLFW.hpp>

#include <GLFW/glfw3.h>

using namespace ax;

InputModuleGLFW* WrapperInputModuleGLFW::m_input = nullptr;

void WrapperInputModuleGLFW::setInput(InputModuleGLFW* input, GLFWwindow* window)
{
    m_input = input;
    glfwSetCursorPosCallback(window, WrapperInputModuleGLFW::cursor_pos_callback);
    glfwSetScrollCallback(window, WrapperInputModuleGLFW::cursor_scroll_callback);
}

void WrapperInputModuleGLFW::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
    m_input->cursorPositionCallback(xpos, -ypos);
}
void WrapperInputModuleGLFW::cursor_scroll_callback(GLFWwindow* window, double xaxis, double yaxis)
{
    m_input->cursorScrollCallback(xaxis, yaxis);
}