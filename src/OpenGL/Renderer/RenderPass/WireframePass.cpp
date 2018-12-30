#include <OpenGL/Renderer/RendererGL.hpp>

#include <OpenGL/Renderer/RendererGL.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Assets/AssetManager.hpp>
#include <Core/Assets/Shader.hpp>

using namespace ax;

WireframePass::WireframePass(RenderContent& content, Viewport& viewport) : RenderPass(content, viewport) {}

void WireframePass::initialize() noexcept
{
    m_viewLocation = glGetUniformLocation(content.wireframeShader, "camera_view");
    m_projectionLocation = glGetUniformLocation(content.wireframeShader, "camera_projection");
    m_transformLocation = glGetUniformLocation(content.wireframeShader, "transform");

    m_renderBuffer = std::make_unique<RenderBuffer>(viewport.resolution);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDisable(GL_CULL_FACE);
}
void WireframePass::terminate() noexcept
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    m_renderBuffer.reset();
}
void WireframePass::updateResolution() noexcept
{
    m_renderBuffer.reset(new RenderBuffer(viewport.resolution));
}
void WireframePass::render(double alpha) noexcept
{
    glUseProgram(content.wireframeShader);

    m_renderBuffer->bindForWriting();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    CameraGL& camera = content.cameras.get(viewport.camera);

    Vector3f eye = camera.transform->getTranslation();
    Vector3f target = camera.transform->getTranslation() + camera.transform->getForwardVector();
    Vector3f up = camera.transform->getUpVector();

    Matrix4f viewMatrix = Matrix4f::lookAt(eye, target, up);

    float aspect = (viewport.size.x * (float)Engine::window().getSize().x) /
        (viewport.size.y * (float)Engine::window().getSize().y);

    Matrix4f projectionMatrix = Matrix4f::perspective(camera.fov, aspect, camera.near, camera.far);

    glUniformMatrix4fv(m_viewLocation, 1, GL_FALSE, viewMatrix.data());
    glUniformMatrix4fv(m_projectionLocation, 1, GL_FALSE, projectionMatrix.data());

    //Setup viewport
    glViewport(0, 0, viewport.resolution.x, viewport.resolution.y);

    for(auto& materialIt : content.materials)
    {
        for(auto& staticmeshId : materialIt.second)
        {
            StaticmeshGL& staticmesh = content.staticmeshes.get(staticmeshId);
            if(staticmesh.mesh)
            {
                MeshGL& mesh = content.meshes.get(staticmesh.mesh);

                glUniformMatrix4fv(m_transformLocation, 1, GL_TRUE, staticmesh.transform->getWorldMatrix().data());

                glBindVertexArray(mesh.vao);
                glDrawArrays(GL_TRIANGLES, 0, mesh.size);
                glBindVertexArray(0);
            }
        }
    }

    //Render texture to backbuffer
    Vector2u windowSize = Engine::window().getSize();
    Vector2u position = Vector2u(
        (unsigned)((float)windowSize.x * viewport.position.x),
        (unsigned)((float)windowSize.y * viewport.position.y)
    );
    Vector2u size = Vector2u(
        (unsigned)((float)windowSize.x * viewport.size.x),
        (unsigned)((float)windowSize.y * viewport.size.y)
    );
    glViewport(position.x, position.y, size.x, size.y);

    glUseProgram(content.renderShader);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    m_renderBuffer->bindForReading();

    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(content.quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    glEnable(GL_DEPTH_TEST);

    glUseProgram(0);
}