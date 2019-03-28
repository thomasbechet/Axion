#pragma once

#include <GLFW/Export.hpp>
#include <GLFW/Input/InputGLFW.hpp>

namespace ax
{
    class AXION_GLFW_API WrapperInputGLFW
    {
    public:
        static void setInput(InputGLFW* input, GLFWwindow* window);

    private:
        static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
        static void cursor_scroll_callback(GLFWwindow* window, double xaxis, double yaxis);

        static InputGLFW* m_input;
    };
}