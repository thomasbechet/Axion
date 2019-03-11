#include <Core/Asset/MaterialManager.hpp>

#include <Core/Logger/Logger.hpp>
#include <Core/Renderer/RendererException.hpp>

#include <vector>

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
AssetReference<Material> MaterialManager::loadFromFile(std::string name, Path file) noexcept
{
    if(exists(name))
    {
        Engine::logger().log("Failed to load material '" + name + "' because it already exists.", Logger::Warning);
        return AssetReference<Material>();
    }

    m_materials.emplace(name, std::make_unique<AssetHolder<Material>>(name));
    if(!m_materials.at(name)->get()->loadFromFile(file))
    {
        m_materials.erase(name);
        return AssetReference<Material>();
    }

    return *m_materials.at(name).get();
}
AssetReference<Material> MaterialManager::loadFromJson(std::string name, const std::string& json) noexcept
{
    if(exists(name))
    {
        Engine::logger().log("Failed to load material '" + name + "' because it already exists.", Logger::Warning);
        return AssetReference<Material>();
    }

    m_materials.emplace(name, std::make_unique<AssetHolder<Material>>(name));
    if(!m_materials.at(name)->get()->loadFromJson(json))
    {
        m_materials.erase(name);
        return AssetReference<Material>();
    }

    return *m_materials.at(name).get();
}
AssetReference<Material> MaterialManager::loadFromMemory(std::string name, const MaterialParameters& params) noexcept
{
    if(exists(name))
    {
        Engine::logger().log("Failed to load material '" + name + "' because it already exists.", Logger::Warning);
        return AssetReference<Material>();
    }

    m_materials.emplace(name, std::make_unique<AssetHolder<Material>>(name));
    if(!m_materials.at(name)->get()->loadFromMemory(params))
    {
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

        material->unload(tryUnloadTexture);

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
bool MaterialManager::exists(std::string name) const noexcept
{
    return m_materials.find(name) != m_materials.end();
}

void MaterialManager::dispose() noexcept
{
    std::vector<std::string> keys;
    keys.reserve(m_materials.size());
    for(auto& it : m_materials)
        keys.emplace_back(it.first);

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