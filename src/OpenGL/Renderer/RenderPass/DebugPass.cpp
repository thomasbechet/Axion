#include <OpenGL/Renderer/RendererGL.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Assets/AssetManager.hpp>

using namespace ax;

void RendererGL::initializeDebug() noexcept
{
    Id handle = Engine::assets().shader.load("renderergl_shader_geometry",
        "../shaders/geometry_pass.vertex",
        "../shaders/geometry_pass.fragment")->handle;
    m_debugPassData.geometryShader = m_shaders.get(handle).programId;

    handle = Engine::assets().shader.load("renderergl_shader_geometry_debug",
        "../shaders/geometry_debug.vertex",
        "../shaders/geometry_debug.fragment")->handle;
    m_debugPassData.debugShader = m_shaders.get(handle).programId;

    m_debugPassData.viewLocation = glGetUniformLocation(m_debugPassData.geometryShader, "camera_view");
    m_debugPassData.projectionLocation = glGetUniformLocation(m_debugPassData.geometryShader, "camera_projection");
    m_debugPassData.transformLocation = glGetUniformLocation(m_debugPassData.geometryShader, "transform");

    m_debugPassData.materialIndexLocation = glGetUniformLocation(m_debugPassData.geometryShader, "material_index");
    m_debugPassData.diffuseTextureLocation = glGetUniformLocation(m_debugPassData.geometryShader, "diffuseTexture");
    m_debugPassData.normalTextureLocation = glGetUniformLocation(m_debugPassData.geometryShader, "normalTexture");
    m_debugPassData.specularTextureLocation = glGetUniformLocation(m_debugPassData.geometryShader, "specularTexture");

    m_debugPassData.gbuffer = std::make_unique<GBuffer>(m_windowSize);

    glDepthFunc(GL_LESS);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}
void RendererGL::renderDebug(double alpha, int mode) noexcept
{
    glUseProgram(m_debugPassData.geometryShader);
    m_debugPassData.gbuffer->bindForWriting();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Bind camera
    CameraGL& camera = m_cameras.get(1);
    
    Vector3f eye = camera.transform->getTranslation();
    Vector3f target = camera.transform->getTranslation() + camera.transform->getForwardVector();
    Vector3f up = camera.transform->getUpVector();

    Matrix4f viewMatrix = Matrix4f::lookAt(eye, target, up);
    Matrix4f projectionMatrix = Matrix4f::perspective(camera.fov, (float)Engine::window().getSize().x / (float)Engine::window().getSize().y, camera.near, camera.far);

    glUniformMatrix4fv(m_debugPassData.viewLocation, 1, GL_FALSE, viewMatrix.data());
    glUniformMatrix4fv(m_debugPassData.projectionLocation, 1, GL_FALSE, projectionMatrix.data());

    //Draw scene
    for(auto& materialIt : m_materials)
    {
        MaterialGL& material = materialIt.first;

        glUniform1ui(m_debugPassData.materialIndexLocation, material.uboIndex);

        if(material.useDiffuseTexture)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_textures.get(material.diffuseTexture).id);
        }

        for(auto& staticmeshId : materialIt.second)
        {
            StaticmeshGL& staticmesh = m_staticmeshes.get(staticmeshId);
            if(staticmesh.mesh)
            {
                MeshGL& mesh = m_meshes.get(staticmesh.mesh);

                glUniformMatrix4fv(m_debugPassData.transformLocation, 1, GL_FALSE, staticmesh.transform->getWorldMatrix().data());

                glBindVertexArray(mesh.vao);
                glDrawArrays(GL_TRIANGLES, 0, mesh.size);
                glBindVertexArray(0);
            }
        }
    }

    //Draw debug
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(m_debugPassData.debugShader);

    m_debugPassData.gbuffer->bindForReading();

    glBindVertexArray(m_quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    glUseProgram(0);
}
void RendererGL::terminateDebug() noexcept
{
    m_debugPassData.gbuffer.reset();
    Engine::assets().shader.unload("renderergl_shader_geometry");
    Engine::assets().shader.unload("renderergl_shader_geometry_debug");
}