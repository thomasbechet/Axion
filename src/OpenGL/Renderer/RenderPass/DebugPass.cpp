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
    m_shaderProgram0 = m_shaders.get(handle).programId;

    handle = Engine::assets().shader.load("renderergl_shader_geometry_debug",
        "../shaders/geometry_debug.vertex",
        "../shaders/geometry_debug.fragment")->handle;
    m_shaderProgram1 = m_shaders.get(handle).programId;

    m_gbuffer = std::make_unique<GBuffer>(m_windowSize);
}
void RendererGL::renderDebug(double alpha, int mode) noexcept
{
    glUseProgram(m_shaderProgram0);
    m_gbuffer->bindForWriting();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Bind camera
    CameraGL& camera = m_cameras.get(1);

    int viewLocation = glGetUniformLocation(m_shaderProgram0, "camera_view");
    int projectionLocation = glGetUniformLocation(m_shaderProgram0, "camera_projection");
    
    Vector3f eye = camera.transform->getTranslation();
    Vector3f target = camera.transform->getTranslation() + camera.transform->getForwardVector();
    Vector3f up = camera.transform->getUpVector();

    Matrix4f viewMatrix = Matrix4f::lookAt(eye, target, up);
    Matrix4f projectionMatrix = Matrix4f::perspective(camera.fov, (float)Engine::window().getSize().x / (float)Engine::window().getSize().y, camera.near, camera.far);

    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, viewMatrix.data());
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, projectionMatrix.data());

    //Draw scene
    for(auto& materialIt : m_materials)
    {
        MaterialGL& material = materialIt.first;

        if(material.useDiffuseTexture)
        {
            glUniform1i(glGetUniformLocation(m_shaderProgram0, "useDiffuse"), true);

            int textureLocation = glGetUniformLocation(m_shaderProgram0, "texture");
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_textures.get(material.diffuseTexture).id);
        }
        else
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glUniform1i(glGetUniformLocation(m_shaderProgram0, "useDiffuse"), false);   
        }

        for(auto& staticmeshId : materialIt.second)
        {
            StaticmeshGL& staticmesh = m_staticmeshes.get(staticmeshId);
            if(staticmesh.mesh)
            {
                MeshGL& mesh = m_meshes.get(staticmesh.mesh);

                int transformLocation = glGetUniformLocation(m_shaderProgram0, "transform");
                glUniformMatrix4fv(transformLocation, 1, GL_FALSE, staticmesh.transform->getWorldMatrix().data());

                glBindVertexArray(mesh.vao);
                glDrawArrays(GL_TRIANGLES, 0, mesh.size);
                glBindVertexArray(0);
            }
        }
    }

    //Draw debug
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLsizei HalfWidth = (GLsizei)(m_windowSize.x / 2);
    GLsizei HalfHeight = (GLsizei)(m_windowSize.y / 2);

    m_gbuffer->bindBuffer(GBuffer::TextureType::Albedo);
    glBlitFramebuffer(0, 0, m_windowSize.x, m_windowSize.y, 0, 0, HalfWidth, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
}
void RendererGL::terminateDebug() noexcept
{
    m_gbuffer.reset();
    Engine::assets().shader.unload("renderergl_shader_geometry");
    Engine::assets().shader.unload("renderergl_shader_geometry_debug");
}