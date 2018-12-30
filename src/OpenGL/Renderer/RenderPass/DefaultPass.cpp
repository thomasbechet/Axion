#include <OpenGL/Renderer/RendererGL.hpp>

#include <OpenGL/Renderer/RendererGL.hpp>
#include <Core/Context/Engine.hpp>
#include <Core/Window/Window.hpp>

using namespace ax;

DefaultPass::DefaultPass(RenderContent& content, Viewport& viewport) : RenderPass(content, viewport) {}

void DefaultPass::initialize() noexcept
{
    m_viewLocation = glGetUniformLocation(content.geometryShader, "camera_view");
    m_projectionLocation = glGetUniformLocation(content.geometryShader, "camera_projection");
    m_transformLocation = glGetUniformLocation(content.geometryShader, "transform");

    m_materialIndexLocation = glGetUniformLocation(content.geometryShader, "material_index");
    m_diffuseTextureLocation = glGetUniformLocation(content.geometryShader, "diffuse_texture");
    m_normalTextureLocation = glGetUniformLocation(content.geometryShader, "normal_texture");
    m_specularTextureLocation = glGetUniformLocation(content.geometryShader, "specular_texture");

    m_pointLightIndexLocation = glGetUniformLocation(content.lightShader, "pointlight_index");
    m_pointLightPositionLocation = glGetUniformLocation(content.lightShader, "pointlight_position");

    m_gbuffer = std::make_unique<GBuffer>(viewport.resolution);
    m_renderBuffer = std::make_unique<RenderBuffer>(viewport.resolution);
}
void DefaultPass::terminate() noexcept
{
    m_renderBuffer.reset();
    m_gbuffer.reset();
}
void DefaultPass::updateResolution() noexcept
{
    m_gbuffer.reset(new GBuffer(viewport.resolution));
    m_renderBuffer.reset(new RenderBuffer(viewport.resolution));
}
void DefaultPass::render(double alpha) noexcept
{
    glDepthFunc(GL_LESS);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glUseProgram(content.geometryShader);
    m_gbuffer->bindForWriting();
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

    //Draw scene
    for(auto& materialIt : content.materials)
    {
        MaterialGL& material = materialIt.first;

        glUniform1ui(m_materialIndexLocation, material.uboIndex);

        if(material.useDiffuseTexture)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, content.textures.get(material.diffuseTexture).id);
        }

        if(material.useNormalTexture)
        {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, content.textures.get(material.normalTexture).id);
        }

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

    //Light pass
    glUseProgram(content.lightShader);
    m_gbuffer->bindForReading();
    m_renderBuffer->bindForWriting();

    glClear(GL_COLOR_BUFFER_BIT);

    for(auto& pointLight : content.pointLights)
    {
        glUniform1ui(m_pointLightIndexLocation, pointLight.uboIndex);
        glUniform4fv(m_pointLightPositionLocation, 1, pointLight.transform->getTranslation().data());

        glBindVertexArray(content.quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
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