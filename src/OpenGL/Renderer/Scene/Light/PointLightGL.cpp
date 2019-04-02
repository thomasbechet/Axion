#include <OpenGL/Renderer/RendererGL.hpp>

using namespace ax;

Id RendererGL::createPointLight()
{
    Id id = m_content.pointLights.add(PointLightGL());
    PointLightGL& light = m_content.pointLights.get(id);

    m_content.pointLightUBO->load(light);
    m_content.pointLightUBO->updateLight(light);

    return id;
}
void RendererGL::destroyPointLight(Id id)
{
    PointLightGL& light = m_content.pointLights.get(id);
    m_content.pointLightUBO->unload(light);
}
void RendererGL::setPointLightTransform(Id id, Transform* transform)
{
    PointLightGL& light = m_content.pointLights.get(id);
    light.transform = transform;
}
void RendererGL::setPointLightParameters(Id id, const PointLightParameters& parameters)
{
    PointLightGL& light = m_content.pointLights.get(id);

    light.color = parameters.color;
    light.radius = parameters.radius;
    light.intensity = parameters.intensity;

    m_content.pointLightUBO->updateLight(light);  
}