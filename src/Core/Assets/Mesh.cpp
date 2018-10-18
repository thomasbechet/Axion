#include <Core/Assets/Mesh.hpp>

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
AssetReference<Mesh> MeshManager::load(std::string name, const std::vector<Vertex>& vertices, bool computeTangent, bool computeNormal) noexcept
{
    if(isLoaded(name))
    {
        Engine::logger().log("Failed to load mesh '" + name + "' because it already exists.", Logger::Warning);
        return AssetReference<Mesh>();
    }

    m_meshes.emplace(name, std::make_unique<AssetHolder<Mesh>>());
    Mesh* mesh = m_meshes.at(name)->get();
    mesh->name = name;

    mesh->vertices = vertices;

    if(computeNormal)
    {
        //Compute normal
        for(size_t i = 0; i < mesh->vertices.size(); i += 3)
        {
            Vector3f& v0 = mesh->vertices[i + 0].position;
            Vector3f& v1 = mesh->vertices[i + 1].position;
            Vector3f& v2 = mesh->vertices[i + 2].position;

            Vector3f a = v2 - v0;
            Vector3f b = v1 - v0;

            Vector3f normal = Vector3f::cross(b, a);

            mesh->vertices[i + 0].normal = normal;
            mesh->vertices[i + 1].normal = normal;
            mesh->vertices[i + 2].normal = normal;
        }
    }

    if(computeTangent)
    {
        //Compute tangent
        for(size_t i = 0; i < mesh->vertices.size(); i += 3)
        {
            Vector3f& v0 = mesh->vertices[i + 0].position;
            Vector3f& v1 = mesh->vertices[i + 1].position;
            Vector3f& v2 = mesh->vertices[i + 2].position;

            Vector2f& uv0 = mesh->vertices[i + 0].uv;
            Vector2f& uv1 = mesh->vertices[i + 1].uv;
            Vector2f& uv2 = mesh->vertices[i + 2].uv;

            Vector3f deltaPos1 = v1 - v0;
            Vector3f deltaPos2 = v2 - v0;

            Vector2f deltaUV1 = uv1 - uv0;
            Vector2f deltaUV2 = uv2 - uv0;

            float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
            Vector3f tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
            //Vector3f bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

            mesh->vertices[i + 0].tangent = tangent;
            mesh->vertices[i + 1].tangent = tangent;
            mesh->vertices[i + 2].tangent = tangent;
        }
    }

    try
    {
        mesh->handle = Engine::renderer().createMesh(mesh->vertices);
    }
    catch(const RendererException& exception)
    {
        Engine::logger().log("Failed to load mesh '" + name + "' from renderer: ", Logger::Warning);
        Engine::logger().log(exception.what(), Logger::Warning);
        m_meshes.erase(name);

        return AssetReference<Mesh>();
    }

    return m_meshes.at(name)->reference();
}
bool MeshManager::unload(std::string name) noexcept
{
    if(!isLoaded(name))
    {
        Engine::logger().log("Failed to unload mesh '" + name + "' because it does not exists.", Logger::Warning);
        return false;
    }

    if(m_meshes.at(name)->referenceCount() > 0) return false;

    try
    {
        Engine::renderer().destroyMesh(m_meshes.at(name)->get()->handle);
    }
    catch(const RendererException& exception)
    {
        Engine::logger().log("Failed to unload mesh '" + name + "' from renderer: ", Logger::Warning);
        Engine::logger().log(exception.what(), Logger::Warning);

        return false;
    }
    
    m_meshes.erase(name);
    
    return true;
}
bool MeshManager::isLoaded(std::string name) const noexcept
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