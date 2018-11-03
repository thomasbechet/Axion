#include <OpenGL/Renderer/RendererGL.hpp>

#include <OpenGL/Renderer/RendererGL.hpp>
#include <Core/Context/Engine.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Assets/AssetManager.hpp>

using namespace ax;

DebugPass::DebugPass(RenderContent& content) : RenderPass(content) {}

void DebugPass::initialize() noexcept
{
    Id handle = Engine::assets().shader.load("renderergl_shader_geometry",
        "../shaders/geometry_pass.vertex",
        "../shaders/geometry_pass.fragment")->handle;
    m_geometryShader = content.shaders.get(handle).programId;

    handle = Engine::assets().shader.load("renderergl_shader_geometry_debug",
        "../shaders/geometry_debug.vertex",
        "../shaders/geometry_debug.fragment")->handle;
    m_debugShader = content.shaders.get(handle).programId;

    m_viewLocation = glGetUniformLocation(m_geometryShader, "camera_view");
    m_projectionLocation = glGetUniformLocation(m_geometryShader, "camera_projection");
    m_transformLocation = glGetUniformLocation(m_geometryShader, "transform");

    m_materialIndexLocation = glGetUniformLocation(m_geometryShader, "material_index");
    m_diffuseTextureLocation = glGetUniformLocation(m_geometryShader, "diffuseTexture");
    m_normalTextureLocation = glGetUniformLocation(m_geometryShader, "normalTexture");
    m_specularTextureLocation = glGetUniformLocation(m_geometryShader, "specularTexture");

    m_gbuffer = std::make_unique<GBuffer>(content.windowSize);

    glDepthFunc(GL_LESS);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}
void DebugPass::terminate() noexcept
{
    m_gbuffer.reset();
    Engine::assets().shader.unload("renderergl_shader_geometry");
    Engine::assets().shader.unload("renderergl_shader_geometry_debug");
}
void DebugPass::updateViewport() noexcept
{
    m_gbuffer.reset(new GBuffer(content.windowSize));
    glViewport(0, 0, content.windowSize.x, content.windowSize.y);
}
void DebugPass::render(double alpha) noexcept
{
    glUseProgram(m_geometryShader);
    m_gbuffer->bindForWriting();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Bind camera
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

                glUniformMatrix4fv(m_transformLocation, 1, GL_FALSE, staticmesh.transform->getWorldMatrix().data());

                glBindVertexArray(mesh.vao);
                glDrawArrays(GL_TRIANGLES, 0, mesh.size);
                glBindVertexArray(0);
            }
        }
    }

    //Draw debug
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(m_debugShader);

    m_gbuffer->bindForReading();

    glBindVertexArray(content.quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    glUseProgram(0);
}
