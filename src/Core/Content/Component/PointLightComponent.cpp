#include <Core/Content/Component/PointLightComponent.hpp>

#include <Core/Renderer/RendererModule.hpp>

using namespace ax;

PointLightComponent::PointLightComponent(const Entity& entity, const Json& json) :
    transform(entity.getComponent<TransformComponent>())
{
    m_handle = Engine::renderer().createPointLight();
    m_handle->setTransform(&transform);

    try
    {
        auto jColor = json.find("color");
        if(jColor != json.end() && jColor->is_array())
            m_parameters.color = Vector3f(*jColor);

        auto jRadius = json.find("radius");
        if(jRadius != json.end() && jRadius->is_number())
            m_parameters.radius = jRadius->get<float>();

        auto jIntensity = json.find("intensity");
        if(jIntensity != json.end() && jIntensity->is_number())
            m_parameters.intensity = jIntensity->get<float>();

        m_handle->setParameters(m_parameters);
    }
    catch(...) {}
}
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