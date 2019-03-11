#include <Core/Asset/ModelManager.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Asset/AssetManager.hpp>
#include <Core/Logger/Logger.hpp>

using namespace ax;

AssetReference<Model> ModelManager::operator()(std::string name) const noexcept
{
    try
    {
        return m_models.at(name)->reference();
    }
    catch(std::out_of_range e)
    {
        Engine::interrupt("Failed to access model '" + name + "'");
    }
}
AssetReference<Model> ModelManager::loadFromFile(std::string name, Path path) noexcept
{
    if(exists(name))
    {
        Engine::logger().log("Failed to load model '" + name + "' because it already exists.", Logger::Warning);
        return AssetReference<Model>();
    }

    m_models.emplace(name, std::make_unique<AssetHolder<Model>>(name));
    if(!m_models.at(name)->get()->loadFromFile(path))
    {
        m_models.erase(name);
        return AssetReference<Model>();
    }

    return m_models.at(name)->reference();
}
AssetReference<Model> ModelManager::loadFromJson(std::string name, std::string json) noexcept
{
    if(exists(name))
    {
        Engine::logger().log("Failed to load model '" + name + "' because it already exists.", Logger::Warning);
        return AssetReference<Model>();
    }

    m_models.emplace(name, std::make_unique<AssetHolder<Model>>(name));
    if(!m_models.at(name)->get()->loadFromJson(json))
    {
        m_models.erase(name);
        return AssetReference<Model>();
    }

    return m_models.at(name)->reference();
}
bool ModelManager::unload(std::string name, bool tryUnloadMeshes, bool tryUnloadMaterials, bool tryUnloadTextures) noexcept
{
    if(!exists(name))
    {
        Engine::logger().log("Failed to unload model '" + name + "' because it does not exists.", Logger::Warning);
        return false;
    }

    if(m_models.at(name)->referenceCount() > 0) return false;

    

    m_models.erase(name);

    return true;
}
bool ModelManager::exists(std::string name) const noexcept
{
    return m_models.find(name) != m_models.end();
}

void ModelManager::dispose() noexcept
{
    std::vector<std::string> keys;
    keys.reserve(m_models.size());
    for(auto& it : m_models)
        keys.emplace_back(it.first);

    for(auto it : keys) unload(it, true, true);
}
void ModelManager::log() const noexcept
{
    Engine::logger().log("[MODEL]", Logger::Info);
    
    for(auto& it : m_models)
    {
        Engine::logger().log(" \\_ " + it.first, Logger::Info);
    }
}

