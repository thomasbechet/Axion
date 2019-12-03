#include <core/content/asset/mesh_asset.hpp>

#include <core/engine/engine.hpp>
#include <core/renderer/renderer_module.hpp>
#include <core/renderer/renderer_exception.hpp>

using namespace ax;

mesh_asset::mesh_asset(const std::string& name, const parameters& parameters) :
    asset(name, identifier),
    m_parameters(parameters)
{

}

const std::vector<vertex>& mesh_asset::get_vertices() const noexcept
{
    return m_parameters.vertices;
}
renderer_mesh_handle mesh_asset::get_handle() const noexcept
{
    return m_handle;
}

bool mesh_asset::on_load() noexcept
{
    if(!m_parameters.source.empty())
    {
        if(!load_from_source(m_parameters.source)) return false;
    }
    else if(!m_parameters.json.is_null())
    {
        if(!load_from_json(m_parameters.json)) return false;
    }
    
    process_geometry();

    return true;
}
bool mesh_asset::on_validate() noexcept
{
    try
    {
        m_handle = engine::renderer().create_mesh(m_parameters.vertices);
    }
    catch(const renderer_exception& exception)
    {
        log_validate_error(exception.what());
        return false;
    }

    return true;
}
bool mesh_asset::on_unload() noexcept
{
    try
    {
        engine::renderer().destroy_mesh(m_handle);
    }
    catch(const renderer_exception& exception)
    {
        log_unload_error(exception.what());
        return false;
    }

    return true;
}

bool mesh_asset::load_from_source(const path& path) noexcept
{
    return true;
}
bool mesh_asset::load_from_json(const json& json) noexcept
{
    return true;
}
void mesh_asset::process_geometry() noexcept
{
    if(m_parameters.compute_normal)
    {
        //Compute normal
        for(size_t i = 0; i < m_parameters.vertices.size(); i += 3)
        {
            vector3f& v0 = m_parameters.vertices[i + 0].position;
            vector3f& v1 = m_parameters.vertices[i + 1].position;
            vector3f& v2 = m_parameters.vertices[i + 2].position;

            vector3f a = v2 - v0;
            vector3f b = v1 - v0;

            vector3f normal = vector3f::cross(b, a);

            m_parameters.vertices[i + 0].normal = normal;
            m_parameters.vertices[i + 1].normal = normal;
            m_parameters.vertices[i + 2].normal = normal;
        }
    }

    if(m_parameters.compute_tangent)
    {
        //Compute tangent
        for(size_t i = 0; i < m_parameters.vertices.size(); i += 3)
        {
            vector3f& v0 = m_parameters.vertices[i + 0].position;
            vector3f& v1 = m_parameters.vertices[i + 1].position;
            vector3f& v2 = m_parameters.vertices[i + 2].position;

            vector2f& uv0 = m_parameters.vertices[i + 0].uv;
            vector2f& uv1 = m_parameters.vertices[i + 1].uv;
            vector2f& uv2 = m_parameters.vertices[i + 2].uv;

            vector3f delta_pos1 = v1 - v0;
            vector3f delta_pos2 = v2 - v0;

            vector2f delta_uv1 = uv1 - uv0;
            vector2f delta_uv2 = uv2 - uv0;

            float r = 1.0f / (delta_uv1.x * delta_uv2.y - delta_uv1.y * delta_uv2.x);
            vector3f tangent = (delta_pos1 * delta_uv2.y - delta_pos2 * delta_uv1.y) * r;
            //Vector3f bitangent = (delta_pos2 * delta_uv1.x - delta_pos1 * delta_uv2.x) * r;

            m_parameters.vertices[i + 0].tangent = tangent;
            m_parameters.vertices[i + 1].tangent = tangent;
            m_parameters.vertices[i + 2].tangent = tangent;
        }
    }
}