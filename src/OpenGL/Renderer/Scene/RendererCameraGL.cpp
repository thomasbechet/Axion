#include <OpenGL/Renderer/Scene/RendererCameraGL.hpp>
#include <OpenGL/Renderer/RendererGL.hpp>

using namespace ax;

RendererCameraHandle RendererGL::createCamera()
{
    Id id = m_content.cameras.add(std::make_unique<RendererCameraGL>());
    RendererCameraGL* camera = m_content.cameras.get(id).get();
    camera->id = id;

    return camera;
}
void RendererGL::destroyCamera(RendererCameraHandle& cameraPointer)
{
    RendererCameraGL* camera = static_cast<RendererCameraGL*>(cameraPointer);
    m_content.cameras.remove(camera->id);
    cameraPointer = nullptr;
}

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