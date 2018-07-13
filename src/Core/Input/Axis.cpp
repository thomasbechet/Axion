#include <Core/Input/Axis.hpp>

#include <Core/Context/Game.hpp>
#include <Core/Input/Input.hpp>

using namespace ax;

Axis::Axis(std::string name) : m_name(name)
{

}

float Axis::delta() noexcept
{
    if(m_type == InputType::Mouse)
    {
        if(m_mouseInput == Mouse::Axis::X)
            return (float)Game::input().getMouseMotion().x * m_sensibility;
        else if(m_mouseInput == Mouse::Axis::Y)
            return (float)Game::input().getMouseMotion().y * m_sensibility;
        else if(m_mouseInput == Mouse::Axis::WheelY)
            return Game::input().getMouseScroll().y;
        else if(m_mouseInput == Mouse::Axis::WheelX)
            return Game::input().getMouseScroll().x;
    }
    else if(m_type == InputType::Gamepad)
    {
        return Game::input().getGamepadAxis(m_gamepadInput);
    }

    return 0.0f;
}

void Axis::bind(Mouse::Axis axis) noexcept
{
    m_type = InputType::Mouse;
    m_mouseInput = axis;
}
void Axis::bind(Gamepad::Axis axis) noexcept
{
    m_type = InputType::Gamepad;
    m_gamepadInput = axis;
}

void Axis::setSensibility(float s) noexcept
{
    m_sensibility = s;
}
float Axis::getSensibility() const noexcept
{
    return m_sensibility;
}

std::string Axis::getName() const noexcept
{
    return m_name;
}
InputType Axis::getType() const noexcept
{
    return m_type;
}