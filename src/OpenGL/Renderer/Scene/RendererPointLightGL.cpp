#include <OpenGL/Renderer/Scene/RendererPointLightGL.hpp>

#include <OpenGL/Renderer/RendererGL.hpp>

using namespace ax;

void RendererPointLightGL::setTransform(Transform* transformPointer) 
{
    transform = transformPointer;
}
void RendererPointLightGL::setParameters(const RendererPointLightParameters& parameters) 
{
    color = parameters.color;
    radius = parameters.radius;
    intensity = parameters.intensity;

    content->pointLightUBO->updateLight(this); 
}