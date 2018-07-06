#pragma once

///////////////
//HEADERS
///////////////
#include <GLFW/Export.hpp>
#include <Core/Input/Input.hpp>

#include <memory>

namespace ax
{
    class AXION_GLFW_API InputGLFW : public Input
    {
    protected:
        void initialize() noexcept override;
        void terminate() noexcept override;

    public:
        KeyboardManager& keyboard() noexcept override;
        MouseManager& mouse() noexcept override;
        JoystickManager& joystick() noexcept override;

    private:
        std::unique_ptr<KeyboardManager> m_keyboard;
        std::unique_ptr<MouseManager> m_mouse;
        std::unique_ptr<JoystickManager> m_joystick;
    };
}