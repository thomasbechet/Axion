#include <OpenGL/Renderer/RenderPass/DebugLightCullingPass.hpp>

#include <OpenGL/Renderer/RendererGL.hpp>
#include <OpenGL/Renderer/Shader/ShaderConstants.hpp>
#include <OpenGL/Renderer/Shader/ShaderConstants.hpp>
#include <Core/Context/Engine.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Asset/AssetManager.hpp>
#include <Core/Asset/Shader.hpp>

using namespace ax;

DebugLightCullingPass::DebugLightCullingPass(RenderContent& content, Viewport& viewport) : RenderPass(content, viewport) {}

void DebugLightCullingPass::initialize() noexcept
{
    glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE);
    glClearDepth(0.0f);
    glDepthFunc(GL_GREATER);
    glEnable(GL_MULTISAMPLE);

    //Load shaders
    m_wireframeShader = content.shaders.get(content.wireframeShader->getHandle()).shader.getProgram();
    m_quadTextureShader = content.shaders.get(content.quadTextureShader->getHandle()).shader.getProgram();
    m_debugLightCullingShader = content.shaders.get(content.debugLightCullingShader->getHandle()).shader.getProgram();

    //Load buffers
    m_renderBuffer = std::make_unique<RenderBuffer>(viewport.resolution);
}
void DebugLightCullingPass::terminate() noexcept
{
    m_renderBuffer.reset();
}
void DebugLightCullingPass::updateResolution() noexcept
{
    m_renderBuffer.reset(new RenderBuffer(viewport.resolution));
}
void DebugLightCullingPass::render(double alpha) noexcept
{
    updateUBOs();
    processCullPass();
    renderScene();
    renderDebug();
    renderViewportPass();
}

void DebugLightCullingPass::updateUBOs() noexcept
{
    //Compute camera matrix
    CameraGL& camera = content.cameras.get(viewport.camera);

    Vector3f eye = camera.transform->getTranslation();
    Vector3f forward = camera.transform->getForwardVector();
    Vector3f up = camera.transform->getUpVector();

    m_viewMatrix = Matrix4f::view(eye, forward, up);

    float aspect = (viewport.size.x * (float)Engine::window().getSize().x) /
        (viewport.size.y * (float)Engine::window().getSize().y);

    Matrix4f projectionMatrix = Matrix4f::perspectiveInversedZ(camera.fov, aspect, camera.near, camera.far);
    Matrix4f invProjectionMatrix = Matrix4f::inverse(projectionMatrix);

    m_vpMatrix = projectionMatrix * m_viewMatrix;

    //Update constants
    content.constantsUBO->setResolution(viewport.resolution);

    //Updates Lights
    content.pointLightUBO->updateMemory(content.pointLights, m_viewMatrix);
    content.directionalLightUBO->updateMemory(content.directionalLights, m_viewMatrix);
    content.cameraUBO->update(m_viewMatrix, projectionMatrix, invProjectionMatrix);
    content.constantsUBO->update();
}
void DebugLightCullingPass::processCullPass() noexcept
{
    glUseProgram(content.lightCullingComputeShader.getProgram());
    Vector2u dispatch = CullLightSSBO::dispatchSize(viewport.resolution);
    glDispatchCompute(dispatch.x, dispatch.y, 1);
}
void DebugLightCullingPass::renderScene() noexcept
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
    content.constantsUBO->update();

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
                glUniformMatrix4fv(MVP_MATRIX_LOCATION, 1, GL_FALSE, mvp.data());

                glBindVertexArray(mesh.vao);
                glDrawArrays(GL_TRIANGLES, 0, mesh.size);
                glBindVertexArray(0);
            }
        }
    }
}
void DebugLightCullingPass::renderDebug() noexcept
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glUseProgram(m_debugLightCullingShader);

    m_renderBuffer->bindForWriting();

    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(content.quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
void DebugLightCullingPass::renderViewportPass() noexcept
{
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

    glUseProgram(m_quadTextureShader);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    m_renderBuffer->bindForReading();

    glBindVertexArray(content.quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    glUseProgram(0);
}