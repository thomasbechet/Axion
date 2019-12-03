#include <core/content/component/shape/uv_sphere_shape_component.hpp>

#include <core/asset/asset_module.ipp>
#include <core/renderer/renderer_module.hpp>
#include <core/math/geometry/uv_sphere.hpp>
#include <core/utility/json_utility.hpp>

using namespace ax;

uv_sphere_shape_component::uv_sphere_shape_component(entity& entity, const json& json) :
    uv_sphere_shape_component(
        entity,
        json_utility::read_float(json, "radius", 1.0f),
        json_utility::read_unsigned(json, "slice", 30),
        json_utility::read_unsigned(json, "stack", 30),
        json_utility::read_boolean(json, "smooth", true),
        json_utility::read_float(json, "factor", 1.0f)
    )
{
    
}
UVSphereShapeComponent::uv_sphere_shape_component(
        Entity& entity,
        float radius,
        unsigned slice,
        unsigned stack,
        bool smooth,
        float factor
    ) :
    uv_sphere(radius, slice, stack),
    transform(entity.get_component<transform_component>()),
    m_smooth(smooth),
    m_coordinate_factor(factor)
{
    //Mesh
    m_mesh = engine::renderer().create_mesh(uv_sphere::vertices(m_radius, m_UN, m_VN, m_smooth, m_coordinate_factor));

    //Staticmesh
    m_staticmesh = engine::renderer().create_staticmesh();
    m_staticmesh->set_transform(&transform);
    m_staticmesh->set_mesh(m_mesh);
    m_material = engine::asset().get<material_asset>(material_asset::default);
    m_staticmesh->set_material(m_material->get_handle());
}
UVSphereShapeComponent::~uv_sphere_shape_component()
{
    engine::renderer().destroy_staticmesh(m_staticmesh);
    engine::renderer().destroy_mesh(m_mesh);
}

void uv_sphere_shape_component::set_material(std::nullptr_t ptr) noexcept
{
    m_material.reset();
    m_staticmesh->set_material(nullptr);
}
void uv_sphere_shape_component::set_material(const std::string& name) noexcept
{
    set_material(engine::asset().get<material_asset>(name));
}
void uv_sphere_shape_component::set_material(_reference<material_asset> material) noexcept
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

void uv_sphere_shape_component::set_smooth(bool smooth) noexcept
{
    m_smooth = smooth;
}
void uv_sphere_shape_component::set_coordinate_factor(float factor) noexcept
{
    m_coordinate_factor = factor;
}

void uv_sphere_shape_component::generate() noexcept
{
    m_mesh->update(uv_sphere::vertices(m_radius, m_UN, m_VN, m_smooth, m_coordinate_factor));
}