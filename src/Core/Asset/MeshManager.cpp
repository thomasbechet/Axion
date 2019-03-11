#include <Core/Asset/MeshManager.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Logger/Logger.hpp>
#include <Core/Renderer/Renderer.hpp>
#include <Core/Renderer/RendererException.hpp>

using namespace ax;

AssetReference<Mesh> MeshManager::operator()(std::string name) const noexcept
{
    try
    {
        return m_meshes.at(name)->reference();
    }   
    catch(std::out_of_range e)
    {
        Engine::interrupt("Failed to access mesh '" + name + "'");
    }
}
AssetReference<Mesh> MeshManager::loadFromJson(std::string name, const std::string& json) noexcept
{
    if(exists(name))
    {
        Engine::logger().log("Failed to load mesh '" + name + "' because it already exists.", Logger::Warning);
        return AssetReference<Mesh>();
    }

    m_meshes.emplace(name, std::make_unique<AssetHolder<Mesh>>(name));
    if(!m_meshes.at(name)->get()->loadFromJson(json))
    {
        m_meshes.erase(name);
        return AssetReference<Mesh>();
    }

    return m_meshes.at(name)->reference();
}
AssetReference<Mesh> MeshManager::loadFromFile(std::string name, Path file) noexcept
{
    if(exists(name))
    {
        Engine::logger().log("Failed to load mesh '" + name + "' because it already exists.", Logger::Warning);
        return AssetReference<Mesh>();
    }

    m_meshes.emplace(name, std::make_unique<AssetHolder<Mesh>>(name));
    if(!m_meshes.at(name)->get()->loadFromFile(file))
    {
        m_meshes.erase(name);
        return AssetReference<Mesh>();
    }

    return m_meshes.at(name)->reference();
}
AssetReference<Mesh> MeshManager::loadFromMemory(std::string name, const std::vector<Vertex>& vertices, bool computeTangent, bool computeNormal) noexcept
{
    if(exists(name))
    {
        Engine::logger().log("Failed to load mesh '" + name + "' because it already exists.", Logger::Warning);
        return AssetReference<Mesh>();
    }

    m_meshes.emplace(name, std::make_unique<AssetHolder<Mesh>>(name));
    if(!m_meshes.at(name)->get()->loadFromMemory(vertices, computeTangent, computeNormal))
    {
        m_meshes.erase(name);
        return AssetReference<Mesh>();
    }

    return m_meshes.at(name)->reference();
}
bool MeshManager::unload(std::string name) noexcept
{
    if(!exists(name))
    {
        Engine::logger().log("Failed to unload mesh '" + name + "' because it does not exists.", Logger::Warning);
        return false;
    }

    if(m_meshes.at(name)->referenceCount() > 0) return false;

    m_meshes.at(name)->get()->unload();
    m_meshes.erase(name);
    
    return true;
}
bool MeshManager::exists(std::string name) const noexcept
{
    return m_meshes.find(name) != m_meshes.end();
}

void MeshManager::dispose() noexcept
{
    std::vector<std::string> keys;
    keys.reserve(m_meshes.size());
    for(auto& it : m_meshes)
        keys.emplace_back(it.first);

    for(auto it : keys) unload(it);
}
void MeshManager::log() const noexcept
{
    Engine::logger().log("[MESH]", Logger::Info);
    
    for(auto& it : m_meshes)
    {
        Engine::logger().log(" \\_ " + it.first, Logger::Info);
    }
}

