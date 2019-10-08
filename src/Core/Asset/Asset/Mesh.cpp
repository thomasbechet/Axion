#include <Core/Asset/Asset/Mesh.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Logger/Logger.hpp>
#include <Core/Renderer/Renderer.hpp>
#include <Core/Renderer/RendererException.hpp>

using namespace ax;

const std::string Mesh::type = "Mesh";

Mesh::Mesh(std::string name, const Parameters& parameters) :
    Asset(name),
    m_parameters(parameters)
{

}

std::string Mesh::getType() const noexcept
{
    return Mesh::type;
}

const std::vector<Vertex>& Mesh::getVertices() const noexcept
{
    return m_parameters.vertices;
}
RendererMeshHandle Mesh::getHandle() const noexcept
{
    return m_handle;
}

bool Mesh::onLoad() noexcept
{
    if(m_parameters.computeNormal)
    {
        //Compute normal
        for(size_t i = 0; i < m_parameters.vertices.size(); i += 3)
        {
            Vector3f& v0 = m_parameters.vertices[i + 0].position;
            Vector3f& v1 = m_parameters.vertices[i + 1].position;
            Vector3f& v2 = m_parameters.vertices[i + 2].position;

            Vector3f a = v2 - v0;
            Vector3f b = v1 - v0;

            Vector3f normal = Vector3f::cross(b, a);

            m_parameters.vertices[i + 0].normal = normal;
            m_parameters.vertices[i + 1].normal = normal;
            m_parameters.vertices[i + 2].normal = normal;
        }
    }

    if(m_parameters.computeTangent)
    {
        //Compute tangent
        for(size_t i = 0; i < m_parameters.vertices.size(); i += 3)
        {
            Vector3f& v0 = m_parameters.vertices[i + 0].position;
            Vector3f& v1 = m_parameters.vertices[i + 1].position;
            Vector3f& v2 = m_parameters.vertices[i + 2].position;

            Vector2f& uv0 = m_parameters.vertices[i + 0].uv;
            Vector2f& uv1 = m_parameters.vertices[i + 1].uv;
            Vector2f& uv2 = m_parameters.vertices[i + 2].uv;

            Vector3f deltaPos1 = v1 - v0;
            Vector3f deltaPos2 = v2 - v0;

            Vector2f deltaUV1 = uv1 - uv0;
            Vector2f deltaUV2 = uv2 - uv0;

            float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
            Vector3f tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
            //Vector3f bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

            m_parameters.vertices[i + 0].tangent = tangent;
            m_parameters.vertices[i + 1].tangent = tangent;
            m_parameters.vertices[i + 2].tangent = tangent;
        }
    }

    return true;
}
bool Mesh::onValidate() noexcept
{
    try
    {
        m_handle = Engine::renderer().createMesh(m_parameters.vertices);
    }
    catch(const RendererException& exception)
    {
        m_error = exception.what();

        return false;
    }

    return true;
}
bool Mesh::onUnload() noexcept
{
    try
    {
        Engine::renderer().destroyMesh(m_handle);
    }
    catch(const RendererException& exception)
    {
        m_error = exception.what();

        return false;
    }

    return true;
}
void Mesh::onError() noexcept
{
    Engine::logger().log(m_error, Logger::Warning);
}