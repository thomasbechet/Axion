#include <GLFW/Input/InputGLFW.hpp>

#include <Core/Input/NullKeyboardManager.hpp>
#include <Core/Input/NullMouseManager.hpp>
#include <Core/Input/NullJoystickManager.hpp>

using namespace ax;

void InputGLFW::initialize() noexcept
{
    m_keyboard = std::make_unique<NullKeyboardManager>();
    m_mouse = std::make_unique<NullMouseManager>();
    m_joystick = std::make_unique<NullJoystickManager>();
}
void InputGLFW::terminate() noexcept
{

}

KeyboardManager& InputGLFW::keyboard() noexcept
{
    return *m_keyboard.get();
}
MouseManager& InputGLFW::mouse() noexcept
{
    return *m_mouse.get();
}
JoystickManager& InputGLFW::joystick() noexcept
{
    return *m_joystick.get();
}