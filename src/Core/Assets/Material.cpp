#include <Core/Assets/AssetManager.hpp>

#include <Core/Context/Game.hpp>
#include <Core/Logger/Logger.hpp>

using namespace ax;

bool AssetManager::loadMaterial(std::string name, MaterialData& material) noexcept
{
    if(materialExists(name))
    {
        Game::logger().log("Failed to load material '" + name + "' because it already exists.", Logger::Warning);
        return false;
    }

    m_materials.emplace(name, std::make_shared<Material>());
    Material* newMaterial = m_materials[name].get();

    if(!material.diffuseTexture.empty())
        newMaterial->diffuseTexture = getTexture(material.diffuseTexture);
    else
        newMaterial->diffuseTexture = nullptr;

    newMaterial->diffuseUniform = material.diffuseUniform;

    if(!material.normalTexture.empty())
        newMaterial->normalTexture = getTexture(material.normalTexture);
    else
        newMaterial->normalTexture = nullptr;

    return true;
}
bool AssetManager::unloadMaterial(std::string name) noexcept
{
    if(!materialExists(name))
    {
        Game::logger().log("Failed to unload material '" + name + "' because it does not exists.", Logger::Warning);
        return false;
    }

    m_materials.erase(name);

    return true;
}
bool AssetManager::materialExists(std::string name) noexcept
{
    return m_materials.find(name) != m_materials.end();
}
std::shared_ptr<const Material> AssetManager::getMaterial(std::string name) noexcept
{
    try
    {
        return std::const_pointer_cast<const Material>(m_materials.at(name));
    }
    catch(std::out_of_range e)
    {
        Game::interrupt("Failed to access material '" + name + "'");
    }   
}