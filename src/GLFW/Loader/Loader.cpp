#include <GLFW/Window/WindowGLFW.hpp>
#include <GLFW/Input/InputGLFW.hpp>

using namespace ax;

extern "C"
{
    Window* create_window()
    {
        return new WindowGLFW();
    }

    Input* create_input()
    {
        return new InputGLFW();
    }
}