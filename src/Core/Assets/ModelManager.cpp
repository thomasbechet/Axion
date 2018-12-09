#include <Core/Assets/ModelManager.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Assets/AssetManager.hpp>
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
AssetReference<Model> ModelManager::create(std::string name, Path path) noexcept
{
    if(exists(name))
    {
        Engine::logger().log("Failed to create model '" + name + "' because it already exists.", Logger::Warning);
        return AssetReference<Model>();
    }

    m_models.emplace(name, std::make_unique<AssetHolder<Model>>(name));
    m_models.at(name)->get()->loadFromFile(path);

    return m_models.at(name)->reference();
}
bool ModelManager::destroy(std::string name, bool tryUnloadMeshes, bool tryUnloadMaterials, bool tryUnloadTextures) noexcept
{
    if(!exists(name))
    {
        Engine::logger().log("Failed to destroy model '" + name + "' because it does not exists.", Logger::Warning);
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

