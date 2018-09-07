#include <Core/Assets/AssetManager.hpp>

#include <Core/Context/Game.hpp>
#include <Core/Logger/Logger.hpp>
#include <Core/Renderer/Renderer.hpp>
#include <Core/Renderer/RendererException.hpp>
#include <Core/Renderer/MaterialSettings.hpp>

using namespace ax;

bool AssetManager::loadMaterial(std::string name, const MaterialData& material) noexcept
{
    if(materialExists(name))
    {
        Game::logger().log("Failed to load material '" + name + "' because it already exists.", Logger::Warning);
        return false;
    }

    m_materials.emplace(name, std::make_shared<Material>());
    Material* newMaterial = m_materials[name].get();
    newMaterial->name = name;

    if(!material.diffuseTexture.empty())
        newMaterial->diffuseTexture = texture(material.diffuseTexture);
    else
        newMaterial->diffuseTexture = nullptr;

    newMaterial->diffuseUniform = material.diffuseUniform;

    if(!material.normalTexture.empty())
        newMaterial->normalTexture = texture(material.normalTexture);
    else
        newMaterial->normalTexture = nullptr;

    MaterialSettings settings;
    settings.diffuseTexture = (newMaterial->diffuseTexture) ? newMaterial->diffuseTexture->handle : 0;
    settings.diffuseColor = newMaterial->diffuseUniform;
    settings.useDiffuseTexture = (newMaterial->diffuseTexture != nullptr);
    settings.normalTexture = (newMaterial->normalTexture) ? newMaterial->normalTexture->handle : 0;
    settings.useNormalTexture = (newMaterial->normalTexture != nullptr);

    try
    {
        newMaterial->handle = Game::renderer().createMaterial(settings);
    }
    catch(const RendererException& exception)
    {
        Game::logger().log("Failed to load material '" + name + "' to renderer: ", Logger::Warning);
        Game::logger().log(exception.what(), Logger::Warning);
        m_materials.erase(name);

        return false;
    }

    return true;
}
bool AssetManager::unloadMaterial(std::string name) noexcept
{
    if(!materialExists(name))
    {
        Game::logger().log("Failed to unload material '" + name + "' because it does not exists.", Logger::Warning);
        return false;
    }

    if(m_materials.at(name).use_count() != 1) return false;

    Material* material = m_materials.at(name).get();

    try
    {
        Game::renderer().destroyMaterial(material->handle);
    }
    catch(const RendererException& exception)
    {
        Game::logger().log("Failed to unload material '" + name + "' from renderer:", Logger::Warning);
        Game::logger().log(exception.what(), Logger::Warning);

        return false;
    }

    if(material->diffuseTexture)
    {
        std::string diffuseTexName = material->diffuseTexture.get()->name;
        material->diffuseTexture.reset();
        unloadTexture(diffuseTexName);
    }

    if(material->normalTexture)
    {
        std::string normalTexName = material->normalTexture.get()->name;
        material->normalTexture.reset();
        unloadTexture(normalTexName);
    }
        
    m_materials.erase(name);

    return true;
}
bool AssetManager::materialExists(std::string name) noexcept
{
    return m_materials.find(name) != m_materials.end();
}
std::shared_ptr<const Material> AssetManager::material(std::string name) noexcept
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