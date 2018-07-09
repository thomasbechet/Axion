#pragma once

//////////////
//HEADERS
//////////////
#include <Core/Export.hpp>

namespace ax
{
    class AXION_CORE_API Button
    {
    public:
        virtual bool isPressed() const noexcept = 0;
        virtual bool isReleased() const noexcept = 0;
        virtual bool isJustPressed() const noexcept = 0;
        virtual bool isJustReleased() const noexcept = 0;

        virtual void bind(Keyboard key) noexcept = 0;
        virtual void bind(MouseButton button) noexcept = 0;
        virtual void bind(JoystickButton button) noexcept = 0;

        InputType getType() const noexcept;

    private:
        InputType m_type = InputType::None;

        Keyboard m_keyboardInput;
        MouseButton m_mouseInput;
        JoystickButton m_joystickInput;
    };
}