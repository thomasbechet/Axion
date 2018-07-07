#include <GLFW/Input/InputGLFW.hpp>

#include <Core/Context/Game.hpp>
#include <Core/Context/GameContext.hpp>
#include <Core/Input/NullKeyboardManager.hpp>
#include <GLFW/Input/KeyboardManagerGLFW.hpp>
#include <Core/Input/NullMouseManager.hpp>
#include <Core/Input/NullJoystickManager.hpp>
#include <GLFW/Window/WindowGLFW.hpp>

#include <GLFW/glfw3.h>

using namespace ax;

void InputGLFW::initialize() noexcept
{
    if(Game::engine().config().getString("Window", "type", "none") != "glfw")
        Game::interrupt("WindowGLFW is required by InputGLFW, please change window's type to 'glfw'");

    GLFWwindow* window = static_cast<WindowGLFW&>(Game::window()).rawWindow();

    m_keyboard = std::make_unique<KeyboardManagerGLFW>(window);
    m_mouse = std::make_unique<NullMouseManager>();
    m_joystick = std::make_unique<NullJoystickManager>();
}
void InputGLFW::terminate() noexcept
{

}
void InputGLFW::update() noexcept
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