#include <OpenGL/Renderer/RendererGL.hpp>

#include <OpenGL/Renderer/RendererGL.hpp>
#include <Core/Context/Engine.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Assets/AssetManager.hpp>

using namespace ax;

DefaultPass::DefaultPass(RenderContent& content) : RenderPass(content) {}

void DefaultPass::initialize() noexcept
{
    Id handle = Engine::assets().shader.create("renderergl_shader_geometry",
        "../shaders/geometry_pass.vertex",
        "../shaders/geometry_pass.fragment")->getHandle();
    m_geometryShader = content.shaders.get(handle).programId;

    handle = Engine::assets().shader.create("renderergl_shader_light",
        "../shaders/light_pass.vertex",
        "../shaders/light_pass.fragment")->getHandle();
    m_lightShader = content.shaders.get(handle).programId;

    m_viewLocation = glGetUniformLocation(m_geometryShader, "camera_view");
    m_projectionLocation = glGetUniformLocation(m_geometryShader, "camera_projection");
    m_transformLocation = glGetUniformLocation(m_geometryShader, "transform");

    m_materialIndexLocation = glGetUniformLocation(m_geometryShader, "material_index");
    m_diffuseTextureLocation = glGetUniformLocation(m_geometryShader, "diffuse_texture");
    m_normalTextureLocation = glGetUniformLocation(m_geometryShader, "normal_texture");
    m_specularTextureLocation = glGetUniformLocation(m_geometryShader, "specular_texture");

    m_pointLightIndexLocation = glGetUniformLocation(m_lightShader, "pointlight_index");
    m_pointLightPositionLocation = glGetUniformLocation(m_lightShader, "pointlight_position");

    m_gbuffer = std::make_unique<GBuffer>(content.windowSize);

    glDepthFunc(GL_LESS);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}
void DefaultPass::terminate() noexcept
{
    m_gbuffer.reset();
    Engine::assets().shader.destroy("renderergl_shader_geometry");
    Engine::assets().shader.destroy("renderergl_shader_light");
}
void DefaultPass::updateViewport() noexcept
{
    m_gbuffer.reset(new GBuffer(content.windowSize));
    glViewport(0, 0, content.windowSize.x, content.windowSize.y);
}
void DefaultPass::render(double alpha) noexcept
{
    glUseProgram(m_geometryShader);
    m_gbuffer->bindForWriting();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    CameraGL& camera = content.cameras.get(1);

    Vector3f eye = camera.transform->getTranslation();
    Vector3f target = camera.transform->getTranslation() + camera.transform->getForwardVector();
    Vector3f up = camera.transform->getUpVector();

    Matrix4f viewMatrix = Matrix4f::lookAt(eye, target, up);
    Matrix4f projectionMatrix = Matrix4f::perspective(camera.fov, (float)Engine::window().getSize().x / (float)Engine::window().getSize().y, camera.near, camera.far);

    glUniformMatrix4fv(m_viewLocation, 1, GL_FALSE, viewMatrix.data());
    glUniformMatrix4fv(m_projectionLocation, 1, GL_FALSE, projectionMatrix.data());

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
    glUseProgram(m_lightShader);
    m_gbuffer->bindForReading();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(auto& pointLight : content.pointLights)
    {
        glUniform1ui(m_pointLightIndexLocation, pointLight.uboIndex);
        glUniform4fv(m_pointLightPositionLocation, 1, pointLight.transform->getTranslation().data());

        glBindVertexArray(content.quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    glUseProgram(0);
}