#include <core/content/component/directional_light_component.hpp>

#include <core/renderer/renderer_module.hpp>
#include <core/utility/json_utility.hpp>

using namespace ax;

directional_light_component::directional_light_component(entity& entity, const json& json) :
    transform(entity.get_component<transform_component>())
{
    m_handle = engine::renderer().create_directional_light();
    m_handle->set_transform(&transform);

    m_parameters.color = json_utility::read_color3(json, "color");
    m_parameters.intensity = json_utility::read_float(json, "intensity", m_parameters.intensity);

    m_handle->set_parameters(m_parameters);
}
directional_light_component::directional_light_component(entity& entity) :
    transform(entity.get_component<transform_component>())
{
    m_handle = engine::renderer().create_directional_light();
    m_handle->set_transform(&transform);
}
directional_light_component::~directional_light_component()
{
    engine::renderer().destroy_directional_light(m_handle);
}

void directional_light_component::set_color(color3 color) noexcept
{
    m_parameters.color = color;
    m_handle->set_parameters(m_parameters);
}
color3 directional_light_component::get_color() const noexcept
{
    return m_parameters.color;
}