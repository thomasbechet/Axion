#include <Core/System/SystemManager.hpp>

#include <iostream>

using namespace ax;

SystemManager::~SystemManager()
{
    removeAll();
}

void SystemManager::start() noexcept
{
    auto sequence = m_sequence;

    for(auto it = sequence.begin(); it != sequence.end(); it++)
        m_systems.at(*it).second->onStart();
}
void SystemManager::stop() noexcept
{
    auto sequence = m_sequence;

    for(auto it = sequence.begin(); it != sequence.end(); it++)
        m_systems.at(*it).second->onStop();
}
void SystemManager::update() noexcept
{
    auto sequence = m_sequence;

    for(auto it = sequence.begin(); it != sequence.end(); it++)
        if(m_systems.at(*it).second->isActive()) m_systems.at(*it).second->onUpdate();
}
void SystemManager::fixedUpdate() noexcept
{
    auto sequence = m_sequence;

    for(auto it = sequence.begin(); it != sequence.end(); it++)
        if(m_systems.at(*it).second->isActive()) m_systems.at(*it).second->onFixedUpdate();
}

void SystemManager::logStates() const noexcept
{
    Game::logger().log("", Logger::Info);
    Game::logger().log("=======SYSTEMS: Sequence=======", Logger::Info);
    for(size_t i = 0; i < m_sequence.size(); i++)
    {
        size_t location = m_sequence.at(i);
        if(m_systems.at(location).second.get()->isActive())
            Game::logger().log("[" + std::to_string(i + 1) + "] : ACTIVE  <" + m_names.at(location) + ">", Logger::Info);
        else
            Game::logger().log("[" + std::to_string(i + 1) + "] : DISABLE <" + m_names.at(location) + ">", Logger::Info);
    }
    Game::logger().log("===============================", Logger::Info);
}

void SystemManager::removeAll() noexcept
{
    for(auto it = m_sequence.begin(); it != m_sequence.end(); it++)
    {
        m_systems.at(*it).first = false;
        m_systems.at(*it).second->onTerminate();
        m_systems.at(*it).second.reset();
    }
    m_sequence.clear();
}