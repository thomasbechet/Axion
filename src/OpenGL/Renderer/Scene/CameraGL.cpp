#include <OpenGL/Renderer/RendererGL.hpp>

using namespace ax;

//Camera
Id RendererGL::createCamera()
{
    Id id = m_content.cameras.add(CameraGL());

    return id;
}
void RendererGL::destroyCamera(Id id)
{
    m_content.cameras.remove(id);
}
void RendererGL::setCameraTransform(Id id, Transform* transform)
{
    CameraGL& camera = m_content.cameras.get(id);
    camera.transform = transform;
}
void RendererGL::setCameraParameters(Id id, const RendererCameraParameters& parameters)
{
    CameraGL& camera = m_content.cameras.get(id);
    camera.fov = parameters.fov;
    camera.near = parameters.near;
    camera.far = parameters.far;
}