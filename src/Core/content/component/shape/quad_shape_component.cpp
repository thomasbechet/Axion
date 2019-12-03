#include <core/content/component/shape/quad_shape_component.hpp>

#include <core/asset/asset_module.ipp>
#include <core/renderer/renderer_module.hpp>
#include <core/utility/json_utility.hpp>

using namespace ax;

quad_shape_component::quad_shape_component(entity& entity, const json& json) :
    quad_shape_component(
        entity,
        json_utility::read_float(json, "x", 1.0f),
        json_utility::read_float(json, "y", 1.0f),
        json_utility::read_float(json, "factor", 1.0f)
    )
{
    
}
quad_shape_component::quad_shape_component(entity& entity, float x, float y, float factor) :
    quad(x, y),
    transform(entity.get_component<transform_component>()),
    m_coordinate_factor(factor)
{
    //Mesh
    m_mesh = engine::renderer().create_mesh(
        quad::vertices(
            m_x, m_y,
            m_coordinate_factor
        )
    );

    //Staticmesh
    m_staticmesh = engine::renderer().create_staticmesh();
    m_staticmesh->set_transform(&transform);
    m_staticmesh->set_mesh(m_mesh);
    m_material = engine::asset().get<material_asset>(material_asset::default);
    m_staticmesh->set_material(m_material->get_handle());
}
quad_shape_component::~quad_shape_component()
{
    engine::renderer().destroy_staticmesh(m_staticmesh);
    engine::renderer().destroy_mesh(m_mesh);
}

void quad_shape_component::set_material(std::nullptr_t ptr) noexcept
{
    m_material.reset();
    m_staticmesh->set_material(nullptr);
}
void quad_shape_component::set_material(const std::string& name) noexcept
{
    set_material(_engine::asset().get<material_asset>(name));
}
void quad_shape_component::set_material(reference<material_asset> material) noexcept
{
    if(material)
    {
        m_material.reset();
        m_material = material;

        m_staticmesh->set_material(m_material->get_handle());
    }
    else
    {
        set_material(nullptr);
    }   
}

void quad_shape_component::set_coordinate_factor(float factor) noexcept
{
    m_coordinate_factor = factor;
}

void quad_shape_component::generate() noexcept
{
    m_mesh->update(quad::vertices(
        m_x, m_y,
        m_coordinate_factor
    ));
}