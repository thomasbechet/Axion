#include <Core/Assets/PackageManager.hpp>

using namespace ax;

AssetReference<Package> PackageManager::operator()(std::string name) const noexcept
{
    try
    {
        return m_packages.at(name)->reference();
    }
    catch(std::out_of_range e)
    {
        Engine::interrupt("Failed to access package '" + name + "'");
    }
}
AssetReference<Package> PackageManager::load(Path path) noexcept
{
    

    return m_packages.at(name)->reference();
}
bool PackageManager::unload(std::string name) noexcept
{
    if(!isLoaded(name))
    {
        Engine::logger().log("Failed to unload package '" + name + "' because it does not exists.", Logger::Warning);
        return false;
    }

    if(m_packages.at(name)->referenceCount() > 0) return false;

    Package* package = m_packages.at(name)->get();

    for(auto it = package->materials.begin(); it != package->materials.end(); it++)
    {
        std::string materialName = it->get()->name;
        it->reset();
        Engine::assets().material.unload(materialName);
    }  
    package->materials.clear();
    for(auto it = package->models.begin(); it != package->models.end(); it++)
    {
        std::string modelName = it->get()->name;
        it->reset();
        Engine::assets().model.unload(modelName);
    }
    package->models.clear();
    for(auto it = package->textures.begin(); it != package->textures.end(); it++)
    {
        std::string textureName = it->get()->name;
        it->reset();
        Engine::assets().texture.unload(textureName);
    }
    package->textures.clear();
    for(auto it = package->meshes.begin(); it != package->meshes.end(); it++)
    {
        std::string meshName = it->get()->name;
        it->reset();
        Engine::assets().mesh.unload(meshName);
    }
    package->meshes.clear();
    for(auto it = package->shaders.begin(); it != package->shaders.end(); it++)
    {
        std::string shaderName = it->get()->name;
        it->reset();
        Engine::assets().shader.unload(shaderName);
    }
    package->shaders.clear();

    m_packages.erase(name);

    return true;
}
bool PackageManager::exists(std::string name) const noexcept
{
    return m_packages.find(name) != m_packages.end();
}

void PackageManager::dispose() noexcept
{
    std::vector<std::string> keys;
    keys.reserve(m_packages.size());
    for(auto& it : m_packages)
        keys.emplace_back(it.first);

    for(auto it : keys) unload(it);
}
void PackageManager::log() const noexcept
{
    Engine::logger().log("[PACKAGE]", Logger::Info);
    
    for(auto& it : m_packages)
    {
        Engine::logger().log(" \\_ " + it.first, Logger::Info);
    }
}