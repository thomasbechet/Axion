#include <OpenGL/Renderer/RendererGL.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Assets/AssetManager.hpp>

using namespace ax;

void RendererGL::initializeDefault() noexcept
{
    Id handle = Engine::assets().shader.load("renderergl_shader_default",
        "../shaders/default.vertex",
        "../shaders/default.fragment")->handle;
    m_defaultPassData.geometryShader = m_shaders.get(handle).programId;

    glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
}
void RendererGL::renderDefault(double alpha) noexcept
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(m_defaultPassData.geometryShader);

    CameraGL& camera = m_cameras.get(1);

    int viewLocation = glGetUniformLocation(m_defaultPassData.geometryShader, "camera_view");
    int projectionLocation = glGetUniformLocation(m_defaultPassData.geometryShader, "camera_projection");

    Vector3f eye = camera.transform->getTranslation();
    Vector3f target = camera.transform->getTranslation() + camera.transform->getForwardVector();
    Vector3f up = camera.transform->getUpVector();

    Matrix4f viewMatrix = Matrix4f::lookAt(eye, target, up);
    Matrix4f projectionMatrix = Matrix4f::perspective(camera.fov, (float)Engine::window().getSize().x / (float)Engine::window().getSize().y, camera.near, camera.far);

    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, viewMatrix.data());
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, projectionMatrix.data());

    for(auto& materialIt : m_materials)
    {
        MaterialGL& material = materialIt.first;

        if(material.useDiffuseTexture)
        {
            glUniform1i(glGetUniformLocation(m_defaultPassData.geometryShader, "useDiffuse"), true);

            int textureLocation = glGetUniformLocation(m_defaultPassData.geometryShader, "texture");
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_textures.get(material.diffuseTexture).id);
        }
        else
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glUniform1i(glGetUniformLocation(m_defaultPassData.geometryShader, "useDiffuse"), false);   
        }

        for(auto& staticmeshId : materialIt.second)
        {
            StaticmeshGL& staticmesh = m_staticmeshes.get(staticmeshId);
            if(staticmesh.mesh)
            {
                MeshGL& mesh = m_meshes.get(staticmesh.mesh);

                int transformLocation = glGetUniformLocation(m_defaultPassData.geometryShader, "transform");
                glUniformMatrix4fv(transformLocation, 1, GL_FALSE, staticmesh.transform->getWorldMatrix().data());

                glBindVertexArray(mesh.vao);
                glDrawArrays(GL_TRIANGLES, 0, mesh.size);
                glBindVertexArray(0);
            }
        }
    }

    glUseProgram(0);
}
void RendererGL::terminateDefault() noexcept
{
    Engine::assets().shader.unload("renderergl_shader_default");
}