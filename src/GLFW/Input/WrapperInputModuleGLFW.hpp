#pragma once

#include <GLFW/Export.hpp>
#include <GLFW/Input/InputModuleGLFW.hpp>

namespace ax
{
    class AXION_GLFW_API WrapperInputModuleGLFW
    {
    public:
        static void setInput(InputModuleGLFW* input, GLFWwindow* window);

    private:
        static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
        static void cursor_scroll_callback(GLFWwindow* window, double xaxis, double yaxis);

        static InputModuleGLFW* m_input;
    };
}