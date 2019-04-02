#include <OpenGL/Renderer/Scene/RendererDirectionalLightGL.hpp>

#include <OpenGL/Renderer/RendererGL.hpp>

using namespace ax;

void RendererDirectionalLightGL::setTransform(Transform* transformPointer)
{   
    transform = transformPointer;
}
void RendererDirectionalLightGL::setParameters(const RendererDirectionalLightParameters& parameters)
{
    color = parameters.color;

    content->directionalLightUBO->updateLight(this);
}