#pragma once

#include <GLFW/Export.hpp>
#include <GLFW/Window/WindowGLFW.hpp>

namespace ax
{
    class AXION_GLFW_API WrapperWindowGLFW
    {
    public:
        static void setWindow(WindowGLFW* window, GLFWwindow* w);

        static void window_pos_callback(GLFWwindow* window, int xpos, int ypos);
        static void window_size_callback(GLFWwindow* window, int width, int height);

    private:
        static WindowGLFW* m_window;
    };
}