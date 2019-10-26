#include <OpenGL/Renderer/Scene/RendererPointLightGL.hpp>
#include <OpenGL/Renderer/RendererModuleGL.hpp>

using namespace ax;

RendererPointLightHandle RendererModuleGL::createPointLight()
{
    Id id = m_content.pointLights.add(std::make_unique<RendererPointLightGL>());
    RendererPointLightGL* pointLight = m_content.pointLights.get(id).get();
    pointLight->id = id;
    pointLight->content = &m_content;

    m_content.pointLightUBO->load(*pointLight);
    m_content.pointLightUBO->updateLight(*pointLight);

    return pointLight;
}
void RendererModuleGL::destroyPointLight(RendererPointLightHandle& pointLightPointer)
{
    RendererPointLightGL* pointLight = static_cast<RendererPointLightGL*>(pointLightPointer);
    m_content.pointLightUBO->unload(*pointLight);
    m_content.pointLights.remove(pointLight->id);

    pointLightPointer = nullptr;
}

void RendererPointLightGL::setTransform(Transform* transformPointer) 
{
    transform = transformPointer;
}
void RendererPointLightGL::setParameters(const RendererPointLightParameters& parameters) 
{
    color = parameters.color;
    radius = parameters.radius;
    intensity = parameters.intensity;

    content->pointLightUBO->updateLight(*this); 
}