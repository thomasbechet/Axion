#include <Core/Content/Component/DirectionalLightComponent.hpp>

#include <Core/Renderer/RendererModule.hpp>

using namespace ax;

DirectionalLightComponent::DirectionalLightComponent(const Entity& entity, const Json& json) :
    transform(entity.getComponent<TransformComponent>())
{
    m_handle = Engine::renderer().createDirectionalLight();
    m_handle->setTransform(&transform);

    try
    {
        auto jColor = json.find("color");
        if(jColor != json.end() && jColor->is_array())
            m_parameters.color = Color3(*jColor);

        auto jIntensity = json.find("intensity");
        if(jIntensity != json.end() && jIntensity->is_number_float())
            m_parameters.intensity = jIntensity->get<float>();
    }
    catch(...) {}

    m_handle->setParameters(m_parameters);
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