#include <Core/Prefabs/Component/CameraComponent.hpp>

#include <Core/Renderer/Renderer.hpp>

using namespace ax;

CameraComponent::CameraComponent(const Entity& entity) :
    transform(entity.getComponent<TransformComponent>())
{
    m_handle = Engine::renderer().createCamera();
    Engine::renderer().setCameraTransform(m_handle, &transform);
    updateRendererParameters();
}
CameraComponent::~CameraComponent()
{
    Engine::renderer().destroyCamera(m_handle);
}

void CameraComponent::bindDefaultViewport() noexcept
{
    Engine::renderer().setViewportCamera(Renderer::DefaultViewport, m_handle);
}
void CameraComponent::bindViewport(Id viewport) noexcept
{   
    Engine::renderer().setViewportCamera(viewport, m_handle);
}

void CameraComponent::setFov(float fov) noexcept
{
    if(fov >= 180.0f) fov = 179.999999f;
    if(fov <= 0.0f) fov = 0.000001f;
    m_parameters.fov = fov;   
    updateRendererParameters();
}
float CameraComponent::getFov() const noexcept
{
    return m_parameters.fov;
}
void CameraComponent::setFarPlane(float far) noexcept
{
    if(far < 0.0f) far = 0.0f;
    if(far < m_parameters.near) far = m_parameters.near;
    m_parameters.far = far;
    updateRendererParameters();
}
float CameraComponent::getFarPlane() const noexcept
{
    return m_parameters.far;
}
void CameraComponent::setNearPlane(float near) noexcept
{
    if(near < 0.0f) near = 0.0f;
    if(near > m_parameters.far) near = m_parameters.far;
    m_parameters.near = near;
    updateRendererParameters();
}
float CameraComponent::getNearPlane() const noexcept
{
    return m_parameters.near;
}

void CameraComponent::updateRendererParameters() noexcept
{
    Engine::renderer().setCameraParameters(m_handle, m_parameters);
}