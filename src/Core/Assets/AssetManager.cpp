#include <Core/Assets/AssetManager.hpp>

#include <Core/Context/Game.hpp>
#include <Core/Logger/Logger.hpp>

using namespace ax;

AssetManager::~AssetManager()
{
    while(m_packages.size() > 0) unloadPackage(m_packages.begin()->first);
}

void AssetManager::logInfo() const noexcept
{
    Game::logger().log("=======Assets: list=======", Logger::Info);
    Game::logger().log("Packages:", Logger::Info);
    for(auto it = m_packages.begin(); it != m_packages.end(); it++)
        Game::logger().log("    -" + it->first, Logger::Info);
    Game::logger().log("Textures:", Logger::Info);
    for(auto it = m_textures.begin(); it != m_textures.end(); it++)
        Game::logger().log("    -" + it->first, Logger::Info);
    Game::logger().log("Meshes:", Logger::Info);
    for(auto it = m_meshes.begin(); it != m_meshes.end(); it++)
        Game::logger().log("    -" + it->first, Logger::Info);
    Game::logger().log("Materials:", Logger::Info);
    for(auto it = m_materials.begin(); it != m_materials.end(); it++)
        Game::logger().log("    -" + it->first, Logger::Info);
    Game::logger().log("Models:", Logger::Info);
    for(auto it = m_models.begin(); it != m_models.end(); it++)
        Game::logger().log("    -" + it->first, Logger::Info);
    Game::logger().log("===========================", Logger::Info);
}
