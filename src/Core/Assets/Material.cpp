#include <Core/Assets/Material.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Assets/AssetManager.hpp>
#include <Core/Logger/Logger.hpp>
#include <Core/Renderer/Renderer.hpp>
#include <Core/Renderer/RendererMaterialParameters.hpp>
#include <Core/Renderer/RendererException.hpp>

using namespace ax;

AssetReference<Material> MaterialManager::operator()(std::string name) const noexcept
{
    try
    {
        return m_materials.at(name)->reference();
    }
    catch(std::out_of_range e)
    {
        Engine::interrupt("Failed to access material '" + name + "'");
    } 
}
AssetReference<Material> MaterialManager::load(std::string name, const MaterialParameters& params) noexcept
{
    if(isLoaded(name))
    {
        Engine::logger().log("Failed to load material '" + name + "' because it already exists.", Logger::Warning);
        return AssetReference<Material>();
    }

    m_materials.emplace(name, std::make_unique<AssetHolder<Material>>());
    Material* material = m_materials.at(name)->get();
    material->name = name;

    if(!params.diffuseTexture.empty())
        material->diffuseTexture = Engine::assets().texture(params.diffuseTexture);

    material->diffuseUniform = params.diffuseUniform;

    if(!params.normalTexture.empty())
        material->normalTexture = Engine::assets().texture(params.normalTexture);

    RendererMaterialParameters settings;
    settings.diffuseTexture = (material->diffuseTexture) ? material->diffuseTexture->handle : 0;
    settings.diffuseColor = material->diffuseUniform;
    settings.useDiffuseTexture = (material->diffuseTexture.isValid());
    settings.normalTexture = (material->normalTexture) ? material->normalTexture->handle : 0;
    settings.useNormalTexture = (material->normalTexture.isValid());

    try
    {
        material->handle = Engine::renderer().createMaterial(settings);
    }
    catch(const RendererException& exception)
    {
        Engine::logger().log("Failed to load material '" + name + "' to renderer: ", Logger::Warning);
        Engine::logger().log(exception.what(), Logger::Warning);
        m_materials.erase(name);

        return AssetReference<Material>();
    }

    return *m_materials.at(name).get();
}
bool MaterialManager::unload(std::string name, bool tryUnloadTexture) noexcept
{
    try
    {
        if(m_materials.at(name)->referenceCount() > 0) return false;
        Material* material = m_materials.at(name)->get();

        if(tryUnloadTexture)
        {
            if(material->diffuseTexture)
            {
                std::string diffuseTexName = material->diffuseTexture->name;
                material->diffuseTexture.reset();
                Engine::assets().texture.unload(diffuseTexName);
            }

            if(material->normalTexture)
            {
                std::string normalTexName = material->normalTexture->name;
                material->normalTexture.reset();
                Engine::assets().texture.unload(normalTexName);
            }
        }

        Engine::renderer().destroyMaterial(material->handle);
        m_materials.erase(name);
    }
    catch(const std::out_of_range& exception)
    {
        Engine::logger().log("Failed to unload material '" + name + "' because it does not exists.", Logger::Warning);
        return false;
    }
    catch(const RendererException& exception)
    {
        Engine::logger().log("Failed to unload material '" + name + "' from renderer:", Logger::Warning);
        Engine::logger().log(exception.what(), Logger::Warning);
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
    for(auto& it : m_materials)
        keys.emplace_back(it.second->get()->name);

    for(auto it : keys) unload(it, true);
}
void MaterialManager::log() const noexcept
{
    Engine::logger().log("[MATERIAL]", Logger::Info);
    
    for(auto& it : m_materials)
    {
        Engine::logger().log(" \\_ " + it.first, Logger::Info);
    }
}