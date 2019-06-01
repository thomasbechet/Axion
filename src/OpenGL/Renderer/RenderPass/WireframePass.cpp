#include <OpenGL/Renderer/RenderPass/WireframePass.hpp>

#include <OpenGL/Renderer/RendererGL.hpp>
#include <OpenGL/Renderer/Shader/ShaderConstants.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Asset/AssetManager.hpp>
#include <Core/Asset/Shader.hpp>

using namespace ax;

WireframePass::WireframePass(RenderContent& content) : RenderPass(content) {}

void WireframePass::onInitialize() noexcept
{
    glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE);
    glClearDepth(0.0f);
    glDepthFunc(GL_GREATER);
    glEnable(GL_MULTISAMPLE);

    //Load shaders
    RendererShaderHandle wireframeShaderHandle = content.wireframeShader->getHandle();
    m_wireframeShader = static_cast<RendererShaderGL&>(*wireframeShaderHandle).shader.getProgram();
    RendererShaderHandle quadTextureShaderHandle = content.quadTextureShader->getHandle();
    m_quadTextureShader = static_cast<RendererShaderGL&>(*quadTextureShaderHandle).shader.getProgram();
}
void WireframePass::onTerminate() noexcept
{

}
void WireframePass::onUpdateResolution(const Vector2u& resolution) noexcept
{
    
}
void WireframePass::onRender(RenderBuffer& renderBuffer, RendererCameraGL& camera, double alpha) noexcept
{
    glDepthFunc(GL_GREATER);
    glClearDepth(0.0f);
    
    glUseProgram(m_wireframeShader);
    renderBuffer->bindForWriting();

    Vector3f eye = camera.transform->getTranslation();
    Vector3f forward = camera.transform->getForwardVector();
    Vector3f up = camera.transform->getUpVector();

    Matrix4f viewMatrix = Matrix4f::view(eye, forward, up);

    float aspect = (viewport.size.x * (float)Engine::window().getSize().x) /
        (viewport.size.y * (float)Engine::window().getSize().y);

    Matrix4f projectionMatrix = Matrix4f::perspectiveInversedZ(camera.fov, aspect, camera.near, camera.far);
    Matrix4f invProjectionMatrix = Matrix4f::inverse(Matrix4f::perspective(camera.fov, aspect, camera.near, camera.far));

    //Update constants
    content.constantsUBO->setViewportResolution(viewport.resolution);

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
        for(auto& staticmesh : materialIt.second)
        {
            if(staticmesh->mesh)
            {
                Matrix4f mvp = vp * staticmesh->transform->getWorldMatrix();
                glUniformMatrix4fv(MVP_MATRIX_LOCATION, 1, GL_FALSE, mvp.data());

                glBindVertexArray(staticmesh->mesh->vao);
                glDrawArrays(GL_TRIANGLES, 0, staticmesh->mesh->size);
                glBindVertexArray(0);
            }
        }
    }
}