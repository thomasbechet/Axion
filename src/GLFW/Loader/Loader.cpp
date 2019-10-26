#include <GLFW/Window/WindowModuleGLFW.hpp>
#include <GLFW/Input/InputModuleGLFW.hpp>

using namespace ax;

extern "C"
{
    WindowModule* create_window()
    {
        return new WindowModuleGLFW();
    }

    InputModule* create_input()
    {
        return new InputModuleGLFW();
    }
}