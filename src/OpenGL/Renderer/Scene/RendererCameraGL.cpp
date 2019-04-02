#include <OpenGL/Renderer/Scene/RendererCameraGL.hpp>

using namespace ax;

void RendererCameraGL::setTransform(Transform* transformPointer)
{
    transform = transformPointer;
}
void RendererCameraGL::setParameters(const RendererCameraParameters& parameters)
{
    fov = parameters.fov;
    near = parameters.near;
    far = parameters.far;
}