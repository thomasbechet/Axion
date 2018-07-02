#include <Core/Input/NullInput.hpp>

#include <Core/Input/NullKeyboardManager.hpp>
#include <Core/Input/NullMouseManager.hpp>
#include <Core/Input/NullJoystickManager.hpp>

using namespace ax;

void NullInput::initialize() noexcept
{
    m_keyboard = std::make_unique<NullKeyboardManager>();
    m_mouse = std::make_unique<NullMouseManager>();
    m_joystick = std::make_unique<NullJoystickManager>();
}
void NullInput::terminate() noexcept
{

}

KeyboardManager& NullInput::keyboard() noexcept
{
    return *m_keyboard.get();
}
MouseManager& NullInput::mouse() noexcept
{
    return *m_mouse.get();
}
JoystickManager& NullInput::joystick() noexcept
{
    return *m_joystick.get();
}