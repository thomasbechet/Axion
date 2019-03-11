#include <Core/Asset/Mesh.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Logger/Logger.hpp>
#include <Core/Renderer/Renderer.hpp>
#include <Core/Renderer/RendererException.hpp>

using namespace ax;

Mesh::Mesh(){}
Mesh::Mesh(std::string name)
{
    m_name = name;
}
Mesh::~Mesh()
{
    unload();
}

bool Mesh::loadFromFile(Path file) noexcept
{
    //TODO

    return false;
}
bool Mesh::loadFromJson(const std::string& json) noexcept
{
    //TODO

    return false;
}
bool Mesh::loadFromMemory(const std::vector<Vertex>& vertices, bool computeTangent, bool computeNormal) noexcept
{
    unload();

    m_vertices = vertices;

    if(computeNormal)
    {
        //Compute normal
        for(size_t i = 0; i < m_vertices.size(); i += 3)
        {
            Vector3f& v0 = m_vertices[i + 0].position;
            Vector3f& v1 = m_vertices[i + 1].position;
            Vector3f& v2 = m_vertices[i + 2].position;

            Vector3f a = v2 - v0;
            Vector3f b = v1 - v0;

            Vector3f normal = Vector3f::cross(b, a);

            m_vertices[i + 0].normal = normal;
            m_vertices[i + 1].normal = normal;
            m_vertices[i + 2].normal = normal;
        }
    }

    if(computeTangent)
    {
        //Compute tangent
        for(size_t i = 0; i < m_vertices.size(); i += 3)
        {
            Vector3f& v0 = m_vertices[i + 0].position;
            Vector3f& v1 = m_vertices[i + 1].position;
            Vector3f& v2 = m_vertices[i + 2].position;

            Vector2f& uv0 = m_vertices[i + 0].uv;
            Vector2f& uv1 = m_vertices[i + 1].uv;
            Vector2f& uv2 = m_vertices[i + 2].uv;

            Vector3f deltaPos1 = v1 - v0;
            Vector3f deltaPos2 = v2 - v0;

            Vector2f deltaUV1 = uv1 - uv0;
            Vector2f deltaUV2 = uv2 - uv0;

            float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
            Vector3f tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
            //Vector3f bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

            m_vertices[i + 0].tangent = tangent;
            m_vertices[i + 1].tangent = tangent;
            m_vertices[i + 2].tangent = tangent;
        }
    }

    try
    {
        m_handle = Engine::renderer().createMesh(m_vertices);
    }
    catch(const RendererException& exception)
    {
        Engine::logger().log("Failed to load mesh '" + m_name + "' from renderer: ", Logger::Warning);
        Engine::logger().log(exception.what(), Logger::Warning);

        return false;
    }

    m_isLoaded = true;

    return true;
}
bool Mesh::unload() noexcept
{
    if(isLoaded())
    {
        try
        {
            Engine::renderer().destroyMesh(m_handle);
        }
        catch(const RendererException& exception)
        {
            Engine::logger().log("Failed to unload mesh '" + m_name + "' from renderer: ", Logger::Warning);
            Engine::logger().log(exception.what(), Logger::Warning);

            return false;
        }
    }

    m_isLoaded = false;

    return true;
}
bool Mesh::isLoaded() const noexcept
{
    return m_isLoaded;
}

std::string Mesh::getName() const noexcept
{
    return m_name;
}

const std::vector<Vertex>& Mesh::getVertices() const noexcept
{
    return m_vertices;
}

Id Mesh::getHandle() const noexcept
{
    return m_handle;
}