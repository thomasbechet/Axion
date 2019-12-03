#include <core/content/component/camera_component.hpp>

#include <core/renderer/renderer_module.hpp>
#include <core/utility/json_utility.hpp>

using namespace ax;

camera_component::camera_component(entity& entity, const json& json) :
    transform(entity.get_component<transform_component>())
{
    m_handle = engine::renderer().create_camera();
    m_handle->set_transform(&transform);

    m_parameters.fov = json_utility::read_float(json, "fov", m_parameters.fov);
    m_parameters.near = json_utility::read_float(json, "near", m_parameters.near);
    m_parameters.far = json_utility::read_float(json, "far", m_parameters.far);

    update_renderer_parameters();
}
camera_component::_camera_component(entity& entity) :
    transform(entity.get_component<transform_component>())
{
    m_handle = engine::renderer().create_camera();
    m_handle->set_transform(&transform);
    update_renderer_parameters();
}
camera_component::~camera_component()
{
    engine::renderer().destroy_camera(m_handle);
}

void camera_component::bind_default_viewport() noexcept
{
    renderer_gui_viewport_handle viewport = engine::renderer().get_default_viewport();
    if(engine::renderer().get_default_viewport()) 
    {
        viewport->set_camera(m_handle);
    }
}
void CameraComponent::bindViewport(renderer_gui_viewport_handle viewport) noexcept
{   
    viewport->set_camera(m_handle);
}

void camera_component::set_fov(float fov) noexcept
{
    if(fov >= 180.0f) fov = 179.999999f;
    if(fov <= 0.0f) fov = 0.000001f;
    m_parameters.fov = fov;   
    update_renderer_parameters();
}
float camera_component::get_fov() const noexcept
{
    return m_parameters.fov;
}
void camera_component::set_far_plane(float far) noexcept
{
    if(far < 0.0f) far = 0.0f;
    if(far < m_parameters.near) far = m_parameters.near;
    m_parameters.far = far;
    update_renderer_parameters();
}
float camera_component::get_far_plane() const noexcept
{
    return m_parameters.far;
}
void camera_component::set_near_plane(float near) noexcept
{
    if(near < 0.0f) near = 0.0f;
    if(near > m_parameters.far) near = m_parameters.far;
    m_parameters.near = near;
    update_renderer_parameters();
}
float camera_component::get_near_plane() const noexcept
{
    return m_parameters.near;
}

void camera_component::update_renderer_parameters() noexcept
{
    m_handle->set_parameters(m_parameters);
}