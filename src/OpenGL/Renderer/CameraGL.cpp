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
void RendererGL::setCameraSettings(Id id, RendererCameraParameters settings)
{
    CameraGL& camera = m_cameras.get(id);
    camera.projection = Matrix4f::perspective();
}