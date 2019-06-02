#include <OpenGL/Renderer/RenderPass/ForwardPlusPass.hpp>

#include <OpenGL/Renderer/RendererGL.hpp>
#include <OpenGL/Renderer/Shader/ShaderConstants.hpp>
#include <Core/Context/Engine.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Asset/AssetManager.hpp>
#include <Core/Asset/Shader.hpp>

using namespace ax;

ForwardPlusPass::ForwardPlusPass(RenderContent& content, RendererGUIViewportGL& viewport, bool lightCullingDebug) : 
    RenderPass(content, viewport),
    m_lightCullingDebug(lightCullingDebug)
{

}

void ForwardPlusPass::onInitialize(const Vector2u& resolution) noexcept
{
    glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE);
    glClearDepth(0.0f);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glDepthRange(0.0f, 1.0f);

    m_resolution = resolution;

    m_buffers = std::make_unique<ForwardPlusBuffers>(m_resolution);

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

    //DebugLightCulling shader
    RendererShaderHandle debugLightCullingShaderHandle = content.debugLightCullingShader->getHandle();
    m_debugLightCullingShader = static_cast<RendererShaderGL&>(*debugLightCullingShaderHandle).shader.getProgram();

    //LightCullingCompute shader
    m_lightCullComputeShader = content.lightCullingComputeShader.getProgram();
}
void ForwardPlusPass::onTerminate() noexcept
{
    //Unload buffers
    m_buffers.reset();
}
void ForwardPlusPass::onUpdateResolution(const Vector2u& resolution) noexcept
{
    m_resolution = resolution;
    m_buffers.reset(new ForwardPlusBuffers(m_resolution));
}
void ForwardPlusPass::onRender(const RenderBuffer& renderBuffer, const RendererCameraGL& camera, double alpha) noexcept
{
    glViewport(0, 0, m_resolution.x, m_resolution.y);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    updateUBOs(camera);
    renderGeometryPass();
    #if (USE_LIGHT_CULLING == 1)
        processCullPass();
    #endif
    renderLightPass();
    renderPPPass(renderBuffer);
    if(m_lightCullingDebug) renderDebug(renderBuffer);
}

void ForwardPlusPass::updateUBOs(const RendererCameraGL& camera) noexcept
{
    Vector3f eye = camera.transform->getTranslation();
    Vector3f forward = camera.transform->getForwardVector();
    Vector3f up = camera.transform->getUpVector();

    m_viewMatrix = Matrix4f::view(eye, forward, up);

    float aspect = (float)viewport.getViewport().width / (float)viewport.getViewport().height;

    Matrix4f projectionMatrix = Matrix4f::perspectiveInversedZ(camera.fov, aspect, camera.near, camera.far);
    Matrix4f invProjectionMatrix = Matrix4f::inverse(projectionMatrix);

    m_vpMatrix = projectionMatrix * m_viewMatrix;

    //Update constants
    content.constantsUBO->setViewportResolution(m_resolution);

    //Updates Lights
    content.pointLightUBO->updateMemory(content.pointLights, m_viewMatrix);
    content.directionalLightUBO->updateMemory(content.directionalLights, m_viewMatrix);
    content.cameraUBO->update(m_viewMatrix, projectionMatrix, invProjectionMatrix);
    content.constantsUBO->update();
}
void ForwardPlusPass::renderGeometryPass() noexcept
{
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
    glUseProgram(m_lightCullComputeShader);
    Vector2u dispatch = CullLightSSBO::dispatchSize(m_resolution);
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
void ForwardPlusPass::renderPPPass(const RenderBuffer& renderBuffer) noexcept
{
    glUseProgram(m_postProcessShader);

    renderBuffer.bindForWriting();
    m_buffers->bindForPPPass();

    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(content.quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
void ForwardPlusPass::renderDebug(const  RenderBuffer& renderBuffer) noexcept
{
    glUseProgram(m_debugLightCullingShader);

    renderBuffer.bindForWriting();

    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(content.quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}