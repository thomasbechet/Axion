#pragma once

#include <GLFW/Export.hpp>
#include <GLFW/Window/WindowModuleGLFW.hpp>

namespace ax
{
    class AXION_GLFW_API WrapperWindowModuleGLFW
    {
    public:
        static void setWindow(WindowModuleGLFW* window, GLFWwindow* w);

        static void window_pos_callback(GLFWwindow* window, int xpos, int ypos);
        static void window_size_callback(GLFWwindow* window, int width, int height);

    private:
        static WindowModuleGLFW* m_window;
    };
}