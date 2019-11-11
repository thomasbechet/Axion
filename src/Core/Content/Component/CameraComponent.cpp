#include <Core/Content/Component/CameraComponent.hpp>

#include <Core/Renderer/RendererModule.hpp>

using namespace ax;

CameraComponent::CameraComponent(const Entity& entity, const Json& json) :
    transform(entity.getComponent<TransformComponent>())
{

}
CameraComponent::CameraComponent(const Entity& entity) :
    transform(entity.getComponent<TransformComponent>())
{
    m_handle = Engine::renderer().createCamera();
    m_handle->setTransform(&transform);
    updateRendererParameters();
}
CameraComponent::~CameraComponent()
{
    Engine::renderer().destroyCamera(m_handle);
}

void CameraComponent::bindDefaultViewport() noexcept
{
    RendererGUIViewportHandle viewport = Engine::renderer().getDefaultViewport();
    if(Engine::renderer().getDefaultViewport()) 
    {
        viewport->setCamera(m_handle);
    }
}
void CameraComponent::bindViewport(RendererGUIViewportHandle viewport) noexcept
{   
    viewport->setCamera(m_handle);
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
    m_handle->setParameters(m_parameters);
}