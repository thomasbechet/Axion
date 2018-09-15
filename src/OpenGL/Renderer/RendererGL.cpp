#include <OpenGL/Renderer/RendererGL.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Window/Window.hpp>

#include <GL/glew.h>

using namespace ax;

void RendererGL::initialize() noexcept
{
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
        Engine::interrupt("Failed to initialize GLEW");
}
void RendererGL::terminate() noexcept
{

}
void RendererGL::update(double alpha) noexcept
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ShaderGL& shader = m_shaders.get(0);
    glUseProgram(shader.programId);

    for(auto mesh : m_meshes)
    {
        glBindVertexArray(mesh.vao);
        glDrawArrays(GL_LINES, 0, mesh.size);
        glBindVertexArray(0);
    }

    glUseProgram(0);
}

//Viewport
void RendererGL::updateViewport() noexcept
{
    Vector2u windowSize = Engine::window().getSize();
    glViewport(0, 0, windowSize.x, windowSize.y);
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