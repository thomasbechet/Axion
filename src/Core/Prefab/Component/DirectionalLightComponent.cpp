#include <Core/Prefab/Component/DirectionalLightComponent.hpp>

#include <Core/Renderer/RendererModule.hpp>

using namespace ax;

DirectionalLightComponent::DirectionalLightComponent(const Entity& entity, const Json& json) :
    transform(entity.getComponent<TransformComponent>())
{

}
DirectionalLightComponent::DirectionalLightComponent(const Entity& entity) :
    transform(entity.getComponent<TransformComponent>())
{
    m_handle = Engine::renderer().createDirectionalLight();
    m_handle->setTransform(&transform);
}
DirectionalLightComponent::~DirectionalLightComponent()
{
    Engine::renderer().destroyDirectionalLight(m_handle);
}

void DirectionalLightComponent::setColor(Color3 color) noexcept
{
    m_parameters.color = color;
    m_handle->setParameters(m_parameters);
}
Color3 DirectionalLightComponent::getColor() const noexcept
{
    return m_parameters.color;
}