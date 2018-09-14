#include <OpenGL/Renderer/RendererGL.hpp>

#include <Core/Context/Game.hpp>
#include <GL/glew.h>

using namespace ax;

void RendererGL::initialize() noexcept
{
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
        Game::interrupt("Failed to initialize GLEW");
}
void RendererGL::terminate() noexcept
{

}
void RendererGL::update(double alpha) noexcept
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

//Viewport
void RendererGL::updateViewport() noexcept
{

}

//Mesh
Id RendererGL::createMesh(
    const std::vector<Vector3f>* positions,
    const std::vector<Vector2f>* uvs,
    const std::vector<Vector3f>* normals,
    const std::vector<Vector3f>* tangents,
    const std::vector<Vector3f>* bitangents
)
{
    return 0;
}
void RendererGL::destroyMesh(Id id)
{

}
//Texture
Id RendererGL::createTexture(
    Vector2u size,
    TextureFormat format,
    const Byte* data
)
{
    return 0;
}
void RendererGL::destroyTexture(Id id)
{

}
//Material
Id RendererGL::createMaterial(RendererMaterialParameters settings)
{
    return 0;
}
void RendererGL::destroyMaterial(Id id)
{

}

//Camera
Id RendererGL::createCamera()
{
    return 0;
}
void RendererGL::destroyCamera(Id id)
{

}
void RendererGL::setCameraTransform(Id id, const Transform& transform)
{

}
void RendererGL::setCameraSettings(Id id, RendererCameraParameters settings)
{

}
//Staticmesh
Id RendererGL::createStaticmesh()
{
    return 0;
}
void RendererGL::destroyStaticmesh(Id id)
{

}
void RendererGL::setStaticmeshMaterial(Id id, Id material)
{

}
void RendererGL::setStaticmeshTransform(Id id, const Transform& transform)
{

}
void RendererGL::setStaticmeshMesh(Id id, Id mesh)
{

}