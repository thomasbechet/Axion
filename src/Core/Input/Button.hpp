#pragma once

#include <Core/Export.hpp>
#include <Core/Input/InputType.hpp>
#include <Core/Input/Keyboard.hpp>
#include <Core/Input/Mouse.hpp>
#include <Core/Input/Gamepad.hpp>

#include <string>

namespace ax
{
    enum class ButtonState
    {
        Pressed,
        Released
    };

    class AXION_CORE_API Button
    {
    public:
        friend class InputModule;

        Button(std::string name);

        bool isPressed() const noexcept;
        bool isReleased() const noexcept;
        bool isJustPressed() const noexcept;
        bool isJustReleased() const noexcept;

        void bind(Keyboard key) noexcept;
        void bind(Mouse::Button button) noexcept;
        void bind(Gamepad::Button button) noexcept;

        InputType getType() const noexcept;
        std::string getName() const noexcept;

    private:
        void update() noexcept;

    private:
        std::string m_name;
        InputType m_type = InputType::None;
        ButtonState m_state = ButtonState::Released;
        ButtonState m_previousState = ButtonState::Released;

        Keyboard m_keyboardInput;
        Mouse::Button m_mouseInput;
        Gamepad::Button m_joystickInput;
    };
}