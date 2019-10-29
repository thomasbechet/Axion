#include <Core/Input/InputModule.hpp>

#include <Core/Context/Engine.hpp>

#include <optional>

using namespace ax;

void InputModule::updateInputs() noexcept
{
    for(auto it = m_buttons.begin(); it != m_buttons.end(); it++)
        it->second.update();
}

Button& InputModule::addButton(std::string name) noexcept
{
    if(m_buttons.find(name) != m_buttons.end())
        Engine::interrupt("Button input <" + name + "> already exists");

    return m_buttons.emplace(name, Button(name)).first->second;
}
Button& InputModule::getButton(std::string name) noexcept
{
    std::optional<std::reference_wrapper<Button>> button;
    try
    {
        button = m_buttons.at(name);
    }
    catch(std::out_of_range e)
    {
        Engine::interrupt("Button input <" + name + "> doesn't exists");
    }

    return button.value();
}
void InputModule::removeButton(std::string name) noexcept
{   
    m_buttons.erase(name);
}

Axis& InputModule::addAxis(std::string name) noexcept
{
    if(m_axis.find(name) != m_axis.end())
        Engine::interrupt("Axis input <" + name + "> already exists");

    return m_axis.emplace(name, Axis(name)).first->second;
}
Axis& InputModule::getAxis(std::string name) noexcept
{
    std::optional<std::reference_wrapper<Axis>> axis;
    try
    {
        axis = m_axis.at(name);
    }
    catch(std::out_of_range e)
    {
        Engine::interrupt("Axis input <" + name + "> doesn't exists");
    }
    
    return axis.value();
}
void InputModule::removeAxis(std::string name) noexcept
{
    m_axis.erase(name);
}