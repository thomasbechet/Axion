#include <Core/Content/Component/PointLightComponent.hpp>

#include <Core/Renderer/RendererModule.hpp>
#include <Core/Utility/JsonUtility.hpp>

using namespace ax;

PointLightComponent::PointLightComponent(Entity& entity, const Json& json) :
    transform(entity.getComponent<TransformComponent>())
{
    m_handle = Engine::renderer().createPointLight();
    m_handle->setTransform(&transform);

    m_parameters.color = JsonUtility::readColor3(json, "color");
    m_parameters.radius = JsonUtility::readFloat(json, "radius", m_parameters.radius);
    m_parameters.intensity = JsonUtility::readFloat(json, "intensity", m_parameters.intensity);

    m_handle->setParameters(m_parameters);
}
PointLightComponent::PointLightComponent(Entity& entity) :
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