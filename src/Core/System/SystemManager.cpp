#include <Core/System/SystemManager.hpp>

#include <iostream>

using namespace ax;

void SystemManager::update() noexcept
{
    std::cout << "update" << std::endl;
}

void SystemManager::logStates() const noexcept
{
    Game::logger().log("=======SYSTEMS: States=======", Logger::Info);
    for(size_t i = 0; i < m_systems.size(); i++)
        if(m_systems.at(i).first)
            if(m_systems.at(i).second.get()->isActive())
                Game::logger().log("[" + std::to_string(i + 1) + "] <" + m_names.at(i) + "> : ACTIVE", Logger::Info);
            else
                Game::logger().log("[" + std::to_string(i + 1) + "] <" + m_names.at(i) + "> : DISABLE", Logger::Info);
    Game::logger().log("==============================", Logger::Info);
}