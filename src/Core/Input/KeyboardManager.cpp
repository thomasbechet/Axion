#include <Core/Input/KeyboardManager.hpp>

#include <Core/Context/Game.hpp>

using namespace ax;

bool KeyboardManager::isKeyPressed(std::string name) const noexcept
{
    try
    {
        return isKeyPressed(m_inputs.at(name));
    }
    catch(std::out_of_range& e)
    {
        Game::interrupt("Keyboard key named '" + name + "' doesn't exists");
        return false;
    }
    
}
bool KeyboardManager::isKeyReleased(std::string name) const noexcept
{
    try
    {
        return isKeyReleased(m_inputs.at(name));
    }
    catch(std::out_of_range& e)
    {
        Game::interrupt("Keyboard key named '" + name + "' doesn't exists");
    }
}

void KeyboardManager::addInput(std::string name, Keyboard key) noexcept
{
    auto it = m_inputs.find(name);
    if(it != m_inputs.end()) Game::interrupt("Keyboard input named '" + name + "' already exists");
    m_inputs.emplace(std::make_pair(name, key));
}
void KeyboardManager::removeInput(std::string name) noexcept
{
    auto it = m_inputs.find(name);
    if(it == m_inputs.end()) Game::interrupt("Keyboard input named '" + name + "' doesn't exists");
    m_inputs.erase(it);
}
Keyboard KeyboardManager::getInput(std::string name) const noexcept
{
    try
    {
        return m_inputs.at(name);
    }
    catch(std::out_of_range& e)
    {
        Game::interrupt("Keyboard input named '" + name + "' doesn't exists");
    }
}
void KeyboardManager::setInput(std::string name, Keyboard key) noexcept
{
    try
    {
        m_inputs.at(name) = key;
    }
    catch(std::out_of_range& e)
    {
        Game::interrupt("Keyboard input named '" + name + "' doesn't exists");
    }
}