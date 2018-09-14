#include <Core/Assets/Material.hpp>

#include <Core/Context/Game.hpp>
#include <Core/Assets/AssetManager.hpp>
#include <Core/Logger/Logger.hpp>
#include <Core/Renderer/Renderer.hpp>
#include <Core/Renderer/RendererMaterialParameters.hpp>
#include <Core/Renderer/RendererException.hpp>

using namespace ax;

std::shared_ptr<const Material> MaterialManager::operator()(std::string name) const noexcept
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
std::shared_ptr<const Material> MaterialManager::load(std::string name, const MaterialParameters& params) noexcept
{
    if(isLoaded(name))
    {
        Game::logger().log("Failed to load material '" + name + "' because it already exists.", Logger::Warning);
        return nullptr;
    }

    m_materials.emplace(name, std::make_shared<Material>());
    Material* material = m_materials.at(name).get();
    material->name = name;

    if(!params.diffuseTexture.empty())
        material->diffuseTexture = Game::assets().texture(params.diffuseTexture);
    else
        material->diffuseTexture = nullptr;

    material->diffuseUniform = params.diffuseUniform;

    if(!params.normalTexture.empty())
        material->normalTexture = Game::assets().texture(params.normalTexture);
    else
        material->normalTexture = nullptr;

    RendererMaterialParameters settings;
    settings.diffuseTexture = (material->diffuseTexture) ? material->diffuseTexture->handle : 0;
    settings.diffuseColor = material->diffuseUniform;
    settings.useDiffuseTexture = (material->diffuseTexture != nullptr);
    settings.normalTexture = (material->normalTexture) ? material->normalTexture->handle : 0;
    settings.useNormalTexture = (material->normalTexture != nullptr);

    try
    {
        material->handle = Game::renderer().createMaterial(settings);
    }
    catch(const RendererException& exception)
    {
        Game::logger().log("Failed to load material '" + name + "' to renderer: ", Logger::Warning);
        Game::logger().log(exception.what(), Logger::Warning);
        m_materials.erase(name);

        return nullptr;
    }

    return std::const_pointer_cast<const Material>(m_materials.at(name));
}
bool MaterialManager::unload(std::string name, bool tryUnloadTexture) noexcept
{
    try
    {
        if(m_materials.at(name).use_count() != 1) return false;
        Material* material = m_materials.at(name).get();

        if(tryUnloadTexture)
        {
            if(material->diffuseTexture)
            {
                std::string diffuseTexName = material->diffuseTexture.get()->name;
                material->diffuseTexture.reset();
                Game::assets().texture.unload(diffuseTexName);
            }

            if(material->normalTexture)
            {
                std::string normalTexName = material->normalTexture.get()->name;
                material->normalTexture.reset();
                Game::assets().texture.unload(normalTexName);
            }
        }

        Game::renderer().destroyMaterial(material->handle);
        m_materials.erase(name);
    }
    catch(const std::out_of_range& exception)
    {
        Game::logger().log("Failed to unload material '" + name + "' because it does not exists.", Logger::Warning);
        return false;
    }
    catch(const RendererException& exception)
    {
        Game::logger().log("Failed to unload material '" + name + "' from renderer:", Logger::Warning);
        Game::logger().log(exception.what(), Logger::Warning);
        return false;
    }

    return true;
}
bool MaterialManager::isLoaded(std::string name) const noexcept
{
    return m_materials.find(name) != m_materials.end();
}

void MaterialManager::dispose() noexcept
{
    std::vector<std::string> keys;
    keys.reserve(m_materials.size());
    for(auto it : m_materials)
        keys.emplace_back(it.second->name);

    for(auto it : keys) unload(it, true);
}
void MaterialManager::log() const noexcept
{
    Game::logger().log("[   MATERIAL  ]", Logger::Info);
    
    for(auto it = m_materials.begin(); it != m_materials.end(); it++)
    {
        Game::logger().log("- " + it->second.get()->name, Logger::Info);
    }
}