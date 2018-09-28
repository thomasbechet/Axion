#include <OpenGL/Renderer/RendererGL.hpp>

using namespace ax;

//Camera
Id RendererGL::createCamera()
{
    Id id = m_cameras.add(CameraGL());

    return id;
}
void RendererGL::destroyCamera(Id id)
{
    m_cameras.remove(id);
}
void RendererGL::setCameraTransform(Id id, Transform* transform)
{
    CameraGL& camera = m_cameras.get(id);
    camera.transform = transform;
}
void RendererGL::setCameraParameters(Id id, RendererCameraParameters parameters)
{
    CameraGL& camera = m_cameras.get(id);
    camera.fov = parameters.fov;
    camera.near = parameters.near;
    camera.far = parameters.far;
}