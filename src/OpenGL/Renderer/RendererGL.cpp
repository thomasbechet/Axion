#include <OpenGL/Renderer/RendererGL.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Assets/AssetManager.hpp>

#include <GL/glew.h>

using namespace ax;

void RendererGL::initialize() noexcept
{
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
        Engine::interrupt("Failed to initialize GLEW");

    MaterialParameters defaultMaterial;
    defaultMaterial.diffuseUniform = Color(1.0f, 1.0f, 1.0f);

    Engine::assets().material.load("default_material", defaultMaterial);
}
void RendererGL::terminate() noexcept
{

}
void RendererGL::update(double alpha) noexcept
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    ShaderGL& shader = m_shaders.get(1);
    glUseProgram(shader.programId);

    CameraGL& camera = m_cameras.get(1);

    int viewLocation = glGetUniformLocation(shader.programId, "camera_view");
    int projectionLocation = glGetUniformLocation(shader.programId, "camera_projection");

    Vector3f eye = camera.transform->getTranslation();
    Vector3f target = camera.transform->getTranslation() + camera.transform->getForwardVector();
    Vector3f up = camera.transform->getUpVector();

    Matrix4f viewMatrix = Matrix4f::lookAt(eye, target, up);
    Matrix4f projectionMatrix = Matrix4f::perspective(camera.fov, (float)Engine::window().getSize().x / (float)Engine::window().getSize().y, camera.near, camera.far);

    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, viewMatrix.data());
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, projectionMatrix.data());

    for(auto& materialIt : m_materials)
    {
        MaterialGL& material = materialIt.second.first;
        for(auto& staticmeshIt : materialIt.second.second)
        {
            StaticmeshGL& staticmesh = m_staticmeshes.get(staticmeshIt);
            if(staticmesh.mesh)
            {
                MeshGL& mesh = m_meshes.get(staticmesh.mesh);

                int transformLocation = glGetUniformLocation(shader.programId, "transform");
                glUniformMatrix4fv(transformLocation, 1, GL_FALSE, staticmesh.transform->getWorldMatrix().data());

                glBindVertexArray(mesh.vao);
                glDrawArrays(GL_TRIANGLES, 0, mesh.size);
                glBindVertexArray(0);
            }
        }
    }

    /*for(auto mesh : m_meshes)
    {
        Matrix4f transform = Matrix4f::identity();

        int transformLocation = glGetUniformLocation(shader.programId, "transform");
        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, transform.data());

        glBindVertexArray(mesh.vao);
        glDrawArrays(GL_TRIANGLES, 0, mesh.size);
        glBindVertexArray(0);
    }*/

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