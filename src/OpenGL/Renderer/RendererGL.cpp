#include <OpenGL/Renderer/RendererGL.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Window/Window.hpp>

#include <GL/glew.h>

#include <iostream>

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
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    ShaderGL& shader = m_shaders.get(0);
    glUseProgram(shader.programId);

    CameraGL& camera = m_cameras.get(0);

    int viewLocation = glGetUniformLocation(shader.programId, "camera_view");
    int projectionLocation = glGetUniformLocation(shader.programId, "camera_projection");

    Vector3f eye = camera.transform->getTranslation();
    Vector3f target = camera.transform->getTranslation() + camera.transform->getForwardVector();
    Vector3f up = camera.transform->getUpVector();

    Matrix4f viewMatrix = Matrix4f::lookAt(eye, target, up);
    Matrix4f projectionMatrix = Matrix4f::perspective(camera.fov, (float)Engine::window().getSize().x / (float)Engine::window().getSize().y, camera.near, camera.far);

    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, viewMatrix.data());
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, projectionMatrix.data());

    for(auto mesh : m_meshes)
    {
        Matrix4f transform = Matrix4f::identity();

        int transformLocation = glGetUniformLocation(shader.programId, "transform");
        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, transform.data());

        glBindVertexArray(mesh.vao);
        glDrawArrays(GL_TRIANGLES, 0, mesh.size);
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
void RendererGL::setStaticmeshTransform(Id id, Transform* transform)
{

}
void RendererGL::setStaticmeshMesh(Id id, Id mesh)
{

}