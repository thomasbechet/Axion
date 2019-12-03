#include <core/content/component/point_light_component.hpp>

#include <core/renderer/renderer_module.hpp>
#include <core/utility/json_utility.hpp>

using namespace ax;

point_light_component::point_light_component(entity& entity, const json& json) :
    transform(entity.get_component<transform_component>())
{
    m_handle = engine::renderer().create_point_light();
    m_handle->set_transform(&transform);

    m_parameters.color = json_utility::read_color3(json, "color");
    m_parameters.radius = json_utility::read_float(json, "radius", m_parameters.radius);
    m_parameters.intensity = json_utility::read_float(json, "intensity", m_parameters.intensity);

    m_handle->set_parameters(m_parameters);
}
point_light_component::point_light_component(_entity& entity) :
    transform(entity.get_component<_transform_component>())
{
    m_handle = engine::renderer().create_point_light();
    m_handle->set_transform(&transform);
}
point_light_component::~point_light_component()
{
    engine::renderer().destroy_point_light(m_handle);
}

void point_light_component::set_radius(float radius) noexcept
{
    m_parameters.radius = radius;
    m_handle->set_parameters(m_parameters);
}
float point_light_component::get_radius() const noexcept
{
    return m_parameters.radius;
}

void point_light_component::set_color(color3 color) noexcept
{
    m_parameters.color = color;
    m_handle->set_parameters(m_parameters);
}
color3 point_light_component::get_color() const noexcept
{
    return m_parameters.color;
}