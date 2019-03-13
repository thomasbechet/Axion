#include <OpenGL/Renderer/RendererGL.hpp>

using namespace ax;

Id RendererGL::createDirectionalLight()
{
    Id id = m_content.directionalLights.add(DirectionalLightGL());
    DirectionalLightGL& light = m_content.directionalLights.get(id);

    m_content.directionalLightUBO->load(light);
    //m_content.pointLightUBO->updateLight(light);

    return id;
}
void RendererGL::destroyDirectionalLight(Id id)
{
    DirectionalLightGL& light = m_content.directionalLights.get(id);
    m_content.directionalLightUBO->unload(light);
}
void RendererGL::setDirectionalLightTransform(Id id, Transform* transform)
{
    DirectionalLightGL& light = m_content.directionalLights.get(id);
    light.transform = transform;
}
void RendererGL::setDirectionalLightParameters(Id id, const DirectionalLightParameters& parameters)
{
    DirectionalLightGL& light = m_content.directionalLights.get(id);

    light.color = parameters.color;

    m_content.directionalLightUBO->updateLight(light);
}