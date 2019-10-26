#include <Core/Input/Button.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Input/InputModule.hpp>

using namespace ax;

Button::Button(std::string name) : m_name(name)
{

}

bool Button::isPressed() const noexcept
{
    return m_state == ButtonState::Pressed;
}
bool Button::isReleased() const noexcept
{
    return m_state == ButtonState::Released;
}
bool Button::isJustPressed() const noexcept
{
    return (isPressed() && m_previousState == ButtonState::Released);
}
bool Button::isJustReleased() const noexcept
{
    return (isReleased() && m_previousState == ButtonState::Pressed);
}

void Button::bind(Keyboard key) noexcept
{
    m_type = InputType::Keyboard;
    m_keyboardInput = key;
    m_state = ButtonState::Released;
    m_previousState = ButtonState::Released;
}
void Button::bind(Mouse::Button button) noexcept
{
    m_type = InputType::Mouse;
    m_mouseInput = button;
    m_state = ButtonState::Released;
    m_previousState = ButtonState::Released;
}
void Button::bind(Gamepad::Button button) noexcept
{
    m_type = InputType::Gamepad;
    m_joystickInput = button;
    m_state = ButtonState::Released;
    m_previousState = ButtonState::Released;
}

InputType Button::getType() const noexcept
{
    return m_type;
}
std::string Button::getName() const noexcept
{
    return m_name;
}

void Button::update() noexcept
{
    m_previousState = m_state;
    switch(m_type)
    {
        case InputType::Keyboard:
            if(Engine::input().isButtonPressed(m_keyboardInput)) m_state = ButtonState::Pressed;
            else m_state = ButtonState::Released;
        break;
        case InputType::Mouse:
            if(Engine::input().isButtonPressed(m_mouseInput)) m_state = ButtonState::Pressed;
            else m_state = ButtonState::Released;
        break;
        case InputType::Gamepad:
            if(Engine::input().isButtonPressed(m_joystickInput)) m_state = ButtonState::Pressed;
            else m_state = ButtonState::Released;
        break;
    }
}
