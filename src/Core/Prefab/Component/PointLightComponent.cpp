#include <Core/Prefab/Component/PointLightComponent.hpp>

#include <Core/Renderer/Renderer.hpp>

using namespace ax;

const std::string PointLightComponent::name = "PointLight";

PointLightComponent::PointLightComponent(const Entity& entity) :
    transform(entity.getComponent<TransformComponent>())
{
    m_handle = Engine::renderer().createPointLight();
    m_handle->setTransform(&transform);
}
PointLightComponent::~PointLightComponent()
{
    Engine::renderer().destroyPointLight(m_handle);
}

void PointLightComponent::setRadius(float radius) noexcept
{
    m_parameters.radius = radius;
    m_handle->setParameters(m_parameters);
}
float PointLightComponent::getRadius() const noexcept
{
    return m_parameters.radius;
}

void PointLightComponent::setColor(Color3 color) noexcept
{
    m_parameters.color = color;
    m_handle->setParameters(m_parameters);
}
Color3 PointLightComponent::getColor() const noexcept
{
    return m_parameters.color;
}