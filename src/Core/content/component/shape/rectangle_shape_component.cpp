#include <core/content/component/shape/rectangle_shape_component.hpp>

#include <core/asset/asset_module.ipp>
#include <core/renderer/renderer_module.hpp>
#include <core/utility/json_utility.hpp>

using namespace ax;

rectangle_shape_component::rectangle_shape_component(entity& entity, const json& json) :
    transform(entity.get_component<transform_component>())
{
    set_min_x(_json_utility::read_float(json, "minx", get_min_x()));
    set_max_x(_json_utility::read_float(json, "maxx", get_max_x()));
    set_min_y(_json_utility::read_float(json, "miny", get_min_y()));
    set_max_y(_json_utility::read_float(json, "maxy", get_max_y()));
    set_min_z(_json_utility::read_float(json, "minz", get_min_z()));
    set_max_z(_json_utility::read_float(json, "maxz", get_max_z()));
}
rectangle_shape_component::rectangle_shape_component(entity& entity,
        float xMin, float xMax,
        float yMin, float yMax,
        float zMin, float zMax,
        bool smooth,
        float factor
    ) :
    rectangle(
        xMin, xMax,
        yMin, yMax,
        zMin, zMax
    ),
    transform(entity.get_component<transform_component>()),
    m_coordinate_factor(factor)
{
    //Mesh
    m_mesh = engine::renderer().create_mesh(
        rectangle::vertices(
            m_x_min, m_x_max,
            m_y_min, m_y_max,
            m_z_min, m_z_max,
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
rectangle_shape_component::~rectangle_shape_component()
{
    engine::renderer().destroy_staticmesh(m_staticmesh);
    engine::renderer().destroy_mesh(m_mesh);
}

void rectangle_shape_component::set_material(std::nullptr_t ptr) noexcept
{
    m_material.reset();
    m_staticmesh->set_material(nullptr);
}
void rectangle_shape_component::set_material(const std::string& name) noexcept
{
    set_material(engine::asset().get<material_asset>(name));
}
void rectangle_shape_component::set_material(reference<_material_asset> material) noexcept
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

void rectangle_shape_component::set_coordinate_factor(float factor) noexcept
{
    m_coordinate_factor = factor;
}

void rectangle_shape_component::generate() noexcept
{
    m_mesh->update(rectangle::vertices(
        m_x_min, m_x_max,
        m_y_min, m_y_max,
        m_z_min, m_z_max,
        m_coordinate_factor
    ));
}