#include <Core/Input/Input.hpp>

#include <Core/Context/Game.hpp>

using namespace ax;

void Input::updateInputs() noexcept
{
    for(auto it = m_buttons.begin(); it != m_buttons.end(); it++)
        it->second.update();
}

Button& Input::addButton(std::string name) noexcept
{
    if(m_buttons.find(name) != m_buttons.end())
        Game::interrupt("Button input <" + name + "> already exists");

    return m_buttons.emplace(name, Button(name)).first->second;
}
Button& Input::getButton(std::string name) noexcept
{
    try
    {
        return m_buttons.at(name);
    }
    catch(std::out_of_range e)
    {
        Game::interrupt("Button input <" + name + "> doesn't exists");
    }
}
void Input::removeButton(std::string name) noexcept
{   
    m_buttons.erase(name);
}

Axis& Input::addAxis(std::string name) noexcept
{
    if(m_axis.find(name) != m_axis.end())
        Game::interrupt("Axis input <" + name + "> already exists");

    return m_axis.emplace(name, Axis(name)).first->second;
}
Axis& Input::getAxis(std::string name) noexcept
{
    try
    {
        return m_axis.at(name);
    }
    catch(std::out_of_range e)
    {
        Game::interrupt("Axis input <" + name + "> doesn't exists");
    }
}
void Input::removeAxis(std::string name) noexcept
{
    m_axis.erase(name);
}