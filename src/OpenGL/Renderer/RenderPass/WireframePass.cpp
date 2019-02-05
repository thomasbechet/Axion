#include <OpenGL/Renderer/RenderPass/WireframePass.hpp>

#include <OpenGL/Renderer/RendererGL.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Asset/AssetManager.hpp>
#include <Core/Asset/Shader.hpp>

using namespace ax;

WireframePass::WireframePass(RenderContent& content, Viewport& viewport) : RenderPass(content, viewport) {}

void WireframePass::initialize() noexcept
{
    glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE);
    glClearDepth(0.0f);
    glDepthFunc(GL_GREATER);

    //Load shaders
    AssetReference<Shader> shader;
    shader = Engine::assets().shader.create("renderergl_shader_wireframe",
        "../shaders/WF_wireframe.vert",
        "../shaders/WF_wireframe.frag");
    if(shader->isLoaded())
        m_wireframeShader = content.shaders.get(shader->getHandle()).shader.getProgram();
    else
        Engine::interrupt("Failed to load shader: renderergl_shader_wireframe");

    //Load uniform locations
    m_mvpLocation = glGetUniformLocation(m_wireframeShader, "mvp");

    //Load buffers
    m_renderBuffer = std::make_unique<RenderBuffer>(viewport.resolution);
}
void WireframePass::terminate() noexcept
{
    //Unload buffers
    m_renderBuffer.reset();

    //Unload shaders
    Engine::assets().shader.destroy("renderergl_shader_wireframe");
}
void WireframePass::updateResolution() noexcept
{
    m_renderBuffer.reset(new RenderBuffer(viewport.resolution));
}
void WireframePass::render(double alpha) noexcept
{
    glDepthFunc(GL_GREATER);
    glClearDepth(0.0f);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glUseProgram(m_wireframeShader);
    m_renderBuffer->bindForWriting();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    CameraGL& camera = content.cameras.get(viewport.camera);

    Vector3f eye = camera.transform->getTranslation();
    Vector3f forward = camera.transform->getForwardVector();
    Vector3f up = camera.transform->getUpVector();

    Matrix4f viewMatrix = Matrix4f::view(eye, forward, up);

    float aspect = (viewport.size.x * (float)Engine::window().getSize().x) /
        (viewport.size.y * (float)Engine::window().getSize().y);

    Matrix4f projectionMatrix = Matrix4f::perspectiveInversedZ(camera.fov, aspect, camera.near, camera.far);
    Matrix4f invProjectionMatrix = Matrix4f::inverse(Matrix4f::perspective(camera.fov, aspect, camera.near, camera.far));

    content.cameraUBO->update(viewMatrix, projectionMatrix, invProjectionMatrix);
    content.shaderConstantsUBO->update();

    Matrix4f vp = projectionMatrix * viewMatrix;

    //Setup viewport
    glViewport(0, 0, viewport.resolution.x, viewport.resolution.y);

    //Render scene
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDisable(GL_CULL_FACE);
    for(auto& materialIt : content.materials)
    {
        for(auto& staticmeshId : materialIt.second)
        {
            StaticmeshGL& staticmesh = content.staticmeshes.get(staticmeshId);
            if(staticmesh.mesh)
            {
                MeshGL& mesh = content.meshes.get(staticmesh.mesh);

                Matrix4f mvp = vp * staticmesh.transform->getWorldMatrix();
                //glUniformMatrix4fv(m_mvpLocation, 1, GL_FALSE, mvp.data());
                glUniformMatrix4fv(m_mvpLocation, 1, GL_FALSE, mvp.data());

                glBindVertexArray(mesh.vao);
                glDrawArrays(GL_TRIANGLES, 0, mesh.size);
                glBindVertexArray(0);
            }
        }
    }

    //Render texture to backbuffer
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
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

    glUseProgram(content.quadRenderShader);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    m_renderBuffer->bindForReading();

    glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glBindVertexArray(content.quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    glEnable(GL_DEPTH_TEST);

    glUseProgram(0);
}