#pragma once

////////////////
//HEADERS
////////////////
#include <GLFW/Export.hpp>
#include <Core/Input/KeyboardManager.hpp>

//Forward declaration
class GLFWwindow;

namespace ax
{
    class AXION_GLFW_API KeyboardManagerGLFW : public KeyboardManager
    {
    public:
        KeyboardManagerGLFW(GLFWwindow* window);

        bool isKeyPressed(Keyboard key) const noexcept override;
        bool isKeyReleased(Keyboard key) const noexcept override;

    private:
        GLFWwindow* m_window = nullptr;
    };
}