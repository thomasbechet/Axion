#include <Core/Assets/ShaderManager.hpp>

using namespace ax;

AssetReference<Shader> ShaderManager::operator()(std::string name) const noexcept
{
    try
    {
        return m_shaders.at(name)->reference();
    }
    catch(std::out_of_range e)
    {
        Engine::interrupt("Failed to access shader '" + name + "'");
    }   
}
AssetReference<Shader> ShaderManager::create(std::string name, Path vertex, Path fragment) noexcept
{
    if(isLoaded(name))
    {
        Engine::logger().log("Failed to create shader '" + name + "' because it already exists.", Logger::Warning);
        return AssetReference<Shader>();
    }

    m_shaders.emplace(name, std::make_unique<AssetHolder<Shader>>(name));
    m_shaders.at(name)->get()->loadFromFile(vertex, fragment);

    return m_shaders.at(name)->reference();
}
bool ShaderManager::destroy(std::string name) noexcept
{
    if(!isLoaded(name))
    {
        Engine::logger().log("Failed to destroy shader '" + name + "' because it does not exists.", Logger::Warning);
        return false;
    }

    if(m_shaders.at(name)->referenceCount() > 0) return false;

    if(!m_shaders.at(name)->get()->unload())
    {
        Engine::logger().log("Failed to unload shader '" + name + "'", Logger::Warning);
        return false;
    }

    m_shaders.erase(name);

    return true;
}
bool ShaderManager::exists(std::string name) const noexcept
{
    return m_shaders.find(name) != m_shaders.end();
}

void ShaderManager::dispose() noexcept
{
    std::vector<std::string> keys;
    keys.reserve(m_shaders.size());
    for(auto& it : m_shaders)
        keys.emplace_back(it.first);

    for(auto it : keys) unload(it);
}
void ShaderManager::log() const noexcept
{
    Engine::logger().log("[SHADER]", Logger::Info);
    
    for(auto& it : m_shaders)
    {
        Engine::logger().log(" \\_ " + it.first, Logger::Info);
    }
}