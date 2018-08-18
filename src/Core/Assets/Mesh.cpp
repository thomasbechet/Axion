#include <Core/Assets/AssetManager.hpp>

#include <Core/Context/Game.hpp>
#include <Core/Logger/Logger.hpp>

using namespace ax;

bool AssetManager::loadMesh(std::string name, const std::vector<Vertex>& vertices) noexcept
{
    if(meshExists(name))
    {
        Game::logger().log("Failed to load mesh '" + name + "' because it already exists.", Logger::Warning);
        return false;
    }

    m_meshes.emplace(name, std::make_shared<Mesh>());
    Mesh* newMesh = m_meshes[name].get();
    newMesh->name = name;

    newMesh->vertex_count = vertices.size();
    newMesh->positions.resize(newMesh->vertex_count);
    newMesh->uvs.resize(newMesh->vertex_count);
    newMesh->normals.resize(newMesh->vertex_count);
    newMesh->tangents.resize(newMesh->vertex_count);
    newMesh->bitangents.resize(newMesh->vertex_count);
    newMesh->colors.resize(newMesh->vertex_count);

    //Copy data
    for(size_t i = 0; i < vertices.size(); i++)
    {
        newMesh->positions[i] = vertices[i].position;
        newMesh->uvs[i] = vertices[i].uv;
        newMesh->normals[i] = vertices[i].normal;
        newMesh->colors[i] = vertices[i].color;
    }

    //Compute tangent and bitangent
    for(size_t i = 0; i < newMesh->vertex_count; i += 3)
    {
        Vector3f& v0 = newMesh->positions[i + 0];
        Vector3f& v1 = newMesh->positions[i + 1];
        Vector3f& v2 = newMesh->positions[i + 2];

        Vector2f& uv0 = newMesh->uvs[i + 0];
        Vector2f& uv1 = newMesh->uvs[i + 1];
        Vector2f& uv2 = newMesh->uvs[i + 2];

        Vector3f deltaPos1 = v1 - v0;
        Vector3f deltaPos2 = v2 - v0;

        Vector2f deltaUV1 = uv1 - uv0;
        Vector2f deltaUV2 = uv2 - uv0;

        float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
        Vector3f tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
        Vector3f bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;
    
        newMesh->tangents.push_back(tangent);
        newMesh->tangents.push_back(tangent);
        newMesh->tangents.push_back(tangent);

        newMesh->bitangents.push_back(bitangent);
        newMesh->bitangents.push_back(bitangent);
        newMesh->bitangents.push_back(bitangent);
    }

    //Upload Mesh --> TODO

    return true;
}
bool AssetManager::unloadMesh(std::string name) noexcept
{
    if(!meshExists(name))
    {
        Game::logger().log("Failed to unload mesh '" + name + "' because it does not exists.", Logger::Warning);
        return false;
    }

    //Unload Mesh --> TODO

    if(m_meshes.at(name).use_count() == 1)
        m_meshes.erase(name);
    
    return true;
}
bool AssetManager::meshExists(std::string name) noexcept
{
    return m_meshes.find(name) != m_meshes.end();
}
std::shared_ptr<const Mesh> AssetManager::getMesh(std::string name) noexcept
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