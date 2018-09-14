#include <Core/Assets/Mesh.hpp>

#include <Core/Context/Game.hpp>
#include <Core/Logger/Logger.hpp>
#include <Core/Renderer/Renderer.hpp>
#include <Core/Renderer/RendererException.hpp>

using namespace ax;

std::shared_ptr<const Mesh> MeshManager::operator()(std::string name) const noexcept
{
    try
    {
        return std::const_pointer_cast<const Mesh>(m_meshes.at(name));
    }   
    catch(std::out_of_range e)
    {
        Game::interrupt("Failed to access mesh '" + name + "'");
    }
}
std::shared_ptr<const Mesh> MeshManager::load(std::string name, const std::vector<Vertex>& vertices) noexcept
{
    if(isLoaded(name))
    {
        Game::logger().log("Failed to load mesh '" + name + "' because it already exists.", Logger::Warning);
        return nullptr;
    }

    m_meshes.emplace(name, std::make_shared<Mesh>());
    Mesh* mesh = m_meshes[name].get();
    mesh->name = name;

    mesh->vertex_count = vertices.size();
    mesh->positions.resize(mesh->vertex_count);
    mesh->uvs.resize(mesh->vertex_count);
    mesh->normals.resize(mesh->vertex_count);
    mesh->tangents.resize(mesh->vertex_count);
    mesh->bitangents.resize(mesh->vertex_count);
    mesh->colors.resize(mesh->vertex_count);

    //Copy data
    for(size_t i = 0; i < vertices.size(); i++)
    {
        mesh->positions[i] = vertices[i].position;
        mesh->uvs[i] = vertices[i].uv;
        mesh->normals[i] = vertices[i].normal;
        mesh->colors[i] = vertices[i].color;
    }

    //Compute tangent and bitangent
    for(size_t i = 0; i < mesh->vertex_count; i += 3)
    {
        Vector3f& v0 = mesh->positions[i + 0];
        Vector3f& v1 = mesh->positions[i + 1];
        Vector3f& v2 = mesh->positions[i + 2];

        Vector2f& uv0 = mesh->uvs[i + 0];
        Vector2f& uv1 = mesh->uvs[i + 1];
        Vector2f& uv2 = mesh->uvs[i + 2];

        Vector3f deltaPos1 = v1 - v0;
        Vector3f deltaPos2 = v2 - v0;

        Vector2f deltaUV1 = uv1 - uv0;
        Vector2f deltaUV2 = uv2 - uv0;

        float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
        Vector3f tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
        Vector3f bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;
    
        mesh->tangents.push_back(tangent);
        mesh->tangents.push_back(tangent);
        mesh->tangents.push_back(tangent);

        mesh->bitangents.push_back(bitangent);
        mesh->bitangents.push_back(bitangent);
        mesh->bitangents.push_back(bitangent);
    }

    try
    {
        mesh->handle = Game::renderer().createMesh(
            &mesh->positions,
            &mesh->uvs,
            &mesh->normals,
            &mesh->tangents,
            &mesh->bitangents
        );
    }
    catch(const RendererException& exception)
    {
        Game::logger().log("Failed to load mesh '" + name + "' from renderer: ", Logger::Warning);
        Game::logger().log(exception.what(), Logger::Warning);
        m_meshes.erase(name);

        return nullptr;
    }

    return m_meshes.at(name);
}
bool MeshManager::unload(std::string name) noexcept
{
    if(!isLoaded(name))
    {
        Game::logger().log("Failed to unload mesh '" + name + "' because it does not exists.", Logger::Warning);
        return false;
    }

    if(m_meshes.at(name).use_count() != 1) return false;

    try
    {
        Game::renderer().destroyMesh(m_meshes.at(name).get()->handle);
    }
    catch(const RendererException& exception)
    {
        Game::logger().log("Failed to unload mesh '" + name + "' from renderer: ", Logger::Warning);
        Game::logger().log(exception.what(), Logger::Warning);

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
    for(auto it : m_meshes)
        keys.emplace_back(it.second->name);

    for(auto it : keys) unload(it);
}
void MeshManager::log() const noexcept
{
    Game::logger().log("[     MESH    ]", Logger::Info);
    
    for(auto it = m_meshes.begin(); it != m_meshes.end(); it++)
    {
        Game::logger().log("- " + it->second.get()->name, Logger::Info);
    }
}