#include <OpenGL/Renderer/Scene/RendererDirectionalLightGL.hpp>
#include <OpenGL/Renderer/RendererModuleGL.hpp>

using namespace ax;

RendererDirectionalLightHandle RendererModuleGL::createDirectionalLight()
{
    Id id = m_content.directionalLights.add(std::make_unique<RendererDirectionalLightGL>());
    RendererDirectionalLightGL* directionalLight = m_content.directionalLights.get(id).get();
    directionalLight->id = id;
    directionalLight->content = &m_content;

    m_content.directionalLightUBO->load(*directionalLight);
    //m_content.pointLightUBO->updateLight(directionalLight);

    return directionalLight;
}
void RendererModuleGL::destroyDirectionalLight(RendererDirectionalLightHandle& directionallightPointer)
{
    RendererDirectionalLightGL* directionalLight = static_cast<RendererDirectionalLightGL*>(directionallightPointer);
    m_content.directionalLightUBO->unload(*directionalLight);
    m_content.directionalLights.remove(directionalLight->id);

    directionallightPointer = nullptr;
}

void RendererDirectionalLightGL::setTransform(TransformComponent* transformPointer)
{   
    transform = transformPointer;
}
void RendererDirectionalLightGL::setParameters(const RendererDirectionalLightParameters& parameters)
{
    color = parameters.color;

    content->directionalLightUBO->updateLight(*this);
}