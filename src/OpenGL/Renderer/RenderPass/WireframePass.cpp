#include <OpenGL/Renderer/RendererGL.hpp>

#include <OpenGL/Renderer/RendererGL.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Assets/AssetManager.hpp>
#include <Core/Assets/Shader.hpp>

using namespace ax;

WireframePass::WireframePass(RenderContent& content) : RenderPass(content) {}

void WireframePass::initialize() noexcept
{
    Id handle = Engine::assets().shader.load("renderergl_shader_wireframe", 
        "../shaders/wireframe.vertex", 
        "../shaders/wireframe.fragment")->handle;

    m_shader = content.shaders.get(handle).programId;
    m_viewLocation = glGetUniformLocation(m_shader, "camera_view");
    m_projectionLocation = glGetUniformLocation(m_shader, "camera_projection");
    m_transformLocation = glGetUniformLocation(m_shader, "transform");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDisable(GL_CULL_FACE);
}
void WireframePass::terminate() noexcept
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    Engine::assets().shader.unload("renderergl_shader_wireframe");
}
void WireframePass::updateViewport() noexcept
{
    glViewport(0, 0, content.windowSize.x, content.windowSize.y);
}
void WireframePass::render(double alpha) noexcept
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(m_shader);

    CameraGL& camera = content.cameras.get(1);

    Vector3f eye = camera.transform->getTranslation();
    Vector3f target = camera.transform->getTranslation() + camera.transform->getForwardVector();
    Vector3f up = camera.transform->getUpVector();

    Matrix4f viewMatrix = Matrix4f::lookAt(eye, target, up);
    Matrix4f projectionMatrix = Matrix4f::perspective(camera.fov, (float)Engine::window().getSize().x / (float)Engine::window().getSize().y, camera.near, camera.far);

    glUniformMatrix4fv(m_viewLocation, 1, GL_FALSE, viewMatrix.data());
    glUniformMatrix4fv(m_projectionLocation, 1, GL_FALSE, projectionMatrix.data());

    for(auto& materialIt : content.materials)
    {
        for(auto& staticmeshId : materialIt.second)
        {
            StaticmeshGL& staticmesh = content.staticmeshes.get(staticmeshId);
            if(staticmesh.mesh)
            {
                MeshGL& mesh = content.meshes.get(staticmesh.mesh);

                glUniformMatrix4fv(m_transformLocation, 1, GL_FALSE, staticmesh.transform->getWorldMatrix().data());

                glBindVertexArray(mesh.vao);
                glDrawArrays(GL_TRIANGLES, 0, mesh.size);
                glBindVertexArray(0);
            }
        }
    }

    glUseProgram(0);
}
