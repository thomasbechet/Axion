#include <GLFW/Input/WrapperInputGLFW.hpp>

#include <GLFW/glfw3.h>

using namespace ax;

InputGLFW* WrapperInputGLFW::m_input = nullptr;

void WrapperInputGLFW::setInput(InputGLFW* input, GLFWwindow* window)
{
    m_input = input;
    glfwSetCursorPosCallback(window, WrapperInputGLFW::cursor_pos_callback);
    glfwSetScrollCallback(window, WrapperInputGLFW::cursor_scroll_callback);
}

void WrapperInputGLFW::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
    //std::cout << "m:" << xpos << " " << ypos << std::endl;

    //int wxpos, wypos;
    //glfwGetWindowPos(window, &wxpos, &wypos);

    //std::cout << "w:" << wxpos << " " << wypos << std::endl;

    //std::cout << "f:" << xpos + (double)wxpos << " " << ypos + (double)wypos << std::endl;

    //m_input->cursorPositionCallback(xpos + (double)wxpos, ypos + (double)wypos);
    m_input->cursorPositionCallback(xpos, -ypos);
}
void WrapperInputGLFW::cursor_scroll_callback(GLFWwindow* window, double xaxis, double yaxis)
{
    m_input->cursorScrollCallback(xaxis, yaxis);
}