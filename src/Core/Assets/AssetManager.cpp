#include <Core/Assets/AssetManager.hpp>

#include <Core/Context/Game.hpp>
#include <Core/Logger/Logger.hpp>

using namespace ax;

AssetManager::~AssetManager()
{
    while(m_packages.size() > 0) unloadPackage(m_packages.begin()->first);
    while(m_models.size() > 0) unloadModel(m_models.begin()->first);
    while(m_materials.size() > 0) unloadMaterial(m_materials.begin()->first);
    while(m_meshes.size() > 0) unloadMesh(m_meshes.begin()->first);
    while(m_textures.size() > 0) unloadTexture(m_textures.begin()->first);
}

void AssetManager::logInfo() const noexcept
{
    Game::logger().log("===========Assets===========", Logger::Info);
    Game::logger().log("Packages:", Logger::Info);
    for(auto it = m_packages.begin(); it != m_packages.end(); it++)
        Game::logger().log("    " + it->first, Logger::Info);
    if(m_packages.empty()) Game::logger().log("    [none]", Logger::Info);
    Game::logger().log("Textures:", Logger::Info);
    for(auto it = m_textures.begin(); it != m_textures.end(); it++)
        Game::logger().log("    " + it->first, Logger::Info);
    if(m_textures.empty()) Game::logger().log("    [none]", Logger::Info);
    Game::logger().log("Meshes:", Logger::Info);
    for(auto it = m_meshes.begin(); it != m_meshes.end(); it++)
        Game::logger().log("    " + it->first, Logger::Info);
    if(m_meshes.empty()) Game::logger().log("    [none]", Logger::Info);
    Game::logger().log("Materials:", Logger::Info);
    for(auto it = m_materials.begin(); it != m_materials.end(); it++)
        Game::logger().log("    " + it->first, Logger::Info);
    if(m_materials.empty()) Game::logger().log("    [none]", Logger::Info);
    Game::logger().log("Models:", Logger::Info);
    for(auto it = m_models.begin(); it != m_models.end(); it++)
        Game::logger().log("    " + it->first, Logger::Info);
    if(m_models.empty()) Game::logger().log("    [none]", Logger::Info);
    Game::logger().log("============================", Logger::Info);
}
