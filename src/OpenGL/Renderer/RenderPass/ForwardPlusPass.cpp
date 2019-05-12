#include <OpenGL/Renderer/RenderPass/ForwardPlusPass.hpp>

#include <OpenGL/Renderer/RendererGL.hpp>
#include <OpenGL/Renderer/Shader/ShaderConstants.hpp>
#include <Core/Context/Engine.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Asset/AssetManager.hpp>
#include <Core/Asset/Shader.hpp>

using namespace ax;

ForwardPlusPass::ForwardPlusPass(RenderContent& content, RendererGUIViewportGL& viewport) : RenderPass(content, viewport) {}

void ForwardPlusPass::initialize() noexcept
{
    glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE);
    glClearDepth(0.0f);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glDepthRange(0.0f, 1.0f);

    m_renderBuffer = std::make_unique<RenderBuffer>(viewport.resolution);
    m_buffers = std::make_unique<ForwardPlusBuffers>(viewport.resolution);

    //Quad
    RendererShaderHandle quadTextureShader = content.quadTextureShader->getHandle();
    m_quadTextureShader = static_cast<RendererShaderGL&>(*quadTextureShader).shader.getProgram();

    //Generic shader
    RendererShaderHandle genericShader = content.genericShader->getHandle();
    m_genericShader = static_cast<RendererShaderGL&>(*genericShader).shader.getProgram();

    //Geometry shader
    RendererShaderHandle geometryShader = content.geometryShader->getHandle();
    m_geometryShader = static_cast<RendererShaderGL&>(*geometryShader).shader.getProgram();

    //PostProcess shader
    RendererShaderHandle postProcessShader = content.postProcessShader->getHandle();
    m_postProcessShader = static_cast<RendererShaderGL&>(*postProcessShader).shader.getProgram();

    //LightCullingCompute shader
    m_lightCullComputeShader = content.lightCullingComputeShader.getProgram();
}
void ForwardPlusPass::terminate() noexcept
{
    //Unload buffers
    m_buffers.reset();
    m_renderBuffer.reset();
}
void ForwardPlusPass::updateResolution() noexcept
{
    m_renderBuffer.reset(new RenderBuffer(viewport.resolution));
    m_buffers.reset(new ForwardPlusBuffers(viewport.resolution));
}
void ForwardPlusPass::render(double alpha) noexcept
{
    updateUBOs();
    renderGeometryPass();
    processCullPass();
    renderLightPass();
    renderPPPass();
    renderViewportPass();   
}
RenderBuffer& ForwardPlusPass::getRenderBuffer() noexcept
{
    return *m_renderBuffer.get();
}

void ForwardPlusPass::updateUBOs() noexcept
{
    //Compute camera matrix
    RendererCameraGL& camera = *viewport.camera;

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
    content.constantsUBO->setViewportResolution(viewport.resolution);

    //Updates Lights
    content.pointLightUBO->updateMemory(content.pointLights, m_viewMatrix);
    content.directionalLightUBO->updateMemory(content.directionalLights, m_viewMatrix);
    content.cameraUBO->update(m_viewMatrix, projectionMatrix, invProjectionMatrix);
    content.constantsUBO->update();
}
void ForwardPlusPass::renderGeometryPass() noexcept
{
    //Viewport setup
    glViewport(0, 0, viewport.resolution.x, viewport.resolution.y);

    //Maybe useless configuration ?
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_GREATER);
    glDepthMask(GL_TRUE); 

    glUseProgram(m_geometryShader);
    m_buffers->bindForGeometryPass();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(auto& materialIt : content.materials)
    {
        RendererMaterialGL& material = *materialIt.first.get();

        glUniform1ui(MATERIAL_INDEX_LOCATION, material.uboIndex);

        if(material.parameters.useNormalTexture)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, static_cast<RendererTextureGL&>(*material.parameters.normalTexture).texture);
        }

        for(auto& staticmesh : materialIt.second)
        {
            if(staticmesh->mesh)
            {
                Matrix4f transform = staticmesh->transform->getWorldMatrix();
                Matrix4f mvp = m_vpMatrix * transform;
                Matrix3f normalToView = Matrix3f(m_viewMatrix) * Matrix3f::transpose(Matrix3f::inverse(Matrix3f(transform)));

                glUniformMatrix4fv(TRANSFORM_MATRIX_LOCATION, 1, GL_FALSE, transform.data());
                glUniformMatrix4fv(MVP_MATRIX_LOCATION, 1, GL_FALSE, mvp.data());
                glUniformMatrix3fv(NORMALTOVIEW_MATRIX_LOCATION, 1, GL_FALSE, normalToView.data());

                glBindVertexArray(staticmesh->mesh->vao);
                glDrawArrays(GL_TRIANGLES, 0, staticmesh->mesh->size);
                glBindVertexArray(0);
            }
        }
    }
}
void ForwardPlusPass::processCullPass() noexcept
{
    glUseProgram(content.lightCullingComputeShader.getProgram());
    Vector2u dispatch = CullLightSSBO::dispatchSize(viewport.resolution);
    glDispatchCompute(dispatch.x, dispatch.y, 1);
}
void ForwardPlusPass::renderLightPass() noexcept
{
    //Draw scene
    glDepthMask(GL_FALSE); 
    glDepthFunc(GL_EQUAL);

    m_buffers->bindForLightPass();    
    glClear(GL_COLOR_BUFFER_BIT);

    for(auto& materialIt : content.materials)
    {
        RendererMaterialGL& material = *materialIt.first.get();

        GLuint shader = (material.parameters.shader) ? static_cast<RendererShaderGL&>(*material.parameters.shader).shader.getProgram() : m_genericShader;
        glUseProgram(shader);

        glUniform1ui(MATERIAL_INDEX_LOCATION, material.uboIndex);

        if(material.parameters.useDiffuseTexture)
        {
            glActiveTexture(GL_TEXTURE0 + DIFFUSE_TEXTURE_BINDING);
            glBindTexture(GL_TEXTURE_2D, static_cast<RendererTextureGL&>(*material.parameters.diffuseTexture).texture);
        }
        if(material.parameters.useNormalTexture)
        {
            glActiveTexture(GL_TEXTURE0 + NORMAL_TEXTURE_BINDING);
            glBindTexture(GL_TEXTURE_2D, static_cast<RendererTextureGL&>(*material.parameters.normalTexture).texture);
        }
        if(material.parameters.useSpecularTexture)
        {
            glActiveTexture(GL_TEXTURE0 + SPECULAR_TEXTURE_BINDING);
            glBindTexture(GL_TEXTURE_2D, static_cast<RendererTextureGL&>(*material.parameters.specularTexture).texture);
        }

        for(auto& staticmesh : materialIt.second)
        {
            if(staticmesh->mesh)
            {
                Matrix4f transform = staticmesh->transform->getWorldMatrix();
                Matrix4f mvp = m_vpMatrix * transform;
                Matrix3f normalToView = Matrix3f(m_viewMatrix) * Matrix3f::transpose(Matrix3f::inverse(Matrix3f(transform)));

                glUniformMatrix4fv(TRANSFORM_MATRIX_LOCATION, 1, GL_FALSE, transform.data());
                glUniformMatrix4fv(MVP_MATRIX_LOCATION, 1, GL_FALSE, mvp.data());
                glUniformMatrix3fv(NORMALTOVIEW_MATRIX_LOCATION, 1, GL_FALSE, normalToView.data());

                glBindVertexArray(staticmesh->mesh->vao);
                glDrawArrays(GL_TRIANGLES, 0, staticmesh->mesh->size);
                glBindVertexArray(0);
            }
        }
    }
}
void ForwardPlusPass::renderPPPass() noexcept
{
    glUseProgram(m_postProcessShader);

    m_renderBuffer->bindForWriting();
    m_buffers->bindForPPPass();

    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(content.quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
void ForwardPlusPass::renderViewportPass() noexcept
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