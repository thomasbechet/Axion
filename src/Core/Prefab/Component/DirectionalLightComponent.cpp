#include <Core/Prefab/Component/DirectionalLightComponent.hpp>

#include <Core/Renderer/Renderer.hpp>

using namespace ax;

const std::string DirectionalLightComponent::name = "DirectionalLight";

DirectionalLightComponent::DirectionalLightComponent(const Entity& entity) :
    transform(entity.getComponent<TransformComponent>())
{
    m_handle = Engine::renderer().createDirectionalLight();
    Engine::renderer().setDirectionalLightTransform(m_handle, &transform);
}
DirectionalLightComponent::~DirectionalLightComponent()
{
    Engine::renderer().destroyDirectionalLight(m_handle);
}

void DirectionalLightComponent::setColor(Color3 color) noexcept
{
    m_parameters.color = color;
    Engine::renderer().setDirectionalLightParameters(m_handle, m_parameters);
}
Color3 DirectionalLightComponent::getColor() const noexcept
{
    return m_parameters.color;
}