#include <Core/Prefabs/Component/PointLightComponent.hpp>

#include <Core/Renderer/Renderer.hpp>

using namespace ax;

PointLightComponent::PointLightComponent(const Entity& entity) :
    transform(entity.getComponent<TransformComponent>())
{
    m_handle = Engine::renderer().createPointLight();
    Engine::renderer().setPointLightTransform(m_handle, &transform);
}
PointLightComponent::~PointLightComponent()
{
    Engine::renderer().destroyPointLight(m_handle);
}

void PointLightComponent::setRadius(float radius) noexcept
{
    m_parameters.radius = radius;
}
float PointLightComponent::getRadius() const noexcept
{
    return m_parameters.radius;
}