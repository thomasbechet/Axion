#include <OpenGL/Renderer/RendererGL.hpp>

#include <Core/Window/Window.hpp>
#include <Core/Assets/AssetManager.hpp>
#include <Core/Assets/Shader.hpp>

using namespace ax;

void RendererGL::initializeWireframe() noexcept
{
    Id handle = Engine::assets().shader.load("renderergl_shader_wireframe", 
        "../shaders/wireframe.vertex", 
        "../shaders/wireframe.fragment")->handle;

    m_wireframePassData.shader = m_shaders.get(handle).programId;
    m_wireframePassData.viewLocation = glGetUniformLocation(m_wireframePassData.shader, "camera_view");
    m_wireframePassData.projectionLocation = glGetUniformLocation(m_wireframePassData.shader, "camera_projection");
    m_wireframePassData.transformLocation = glGetUniformLocation(m_wireframePassData.shader, "transform");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDisable(GL_CULL_FACE);
}
void RendererGL::renderWireframe(double alpha) noexcept
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(m_wireframePassData.shader);

    CameraGL& camera = m_cameras.get(1);

    Vector3f eye = camera.transform->getTranslation();
    Vector3f target = camera.transform->getTranslation() + camera.transform->getForwardVector();
    Vector3f up = camera.transform->getUpVector();

    Matrix4f viewMatrix = Matrix4f::lookAt(eye, target, up);
    Matrix4f projectionMatrix = Matrix4f::perspective(camera.fov, (float)Engine::window().getSize().x / (float)Engine::window().getSize().y, camera.near, camera.far);

    glUniformMatrix4fv(m_wireframePassData.viewLocation, 1, GL_FALSE, viewMatrix.data());
    glUniformMatrix4fv(m_wireframePassData.projectionLocation, 1, GL_FALSE, projectionMatrix.data());

    for(auto& materialIt : m_materials)
    {
        for(auto& staticmeshId : materialIt.second)
        {
            StaticmeshGL& staticmesh = m_staticmeshes.get(staticmeshId);
            if(staticmesh.mesh)
            {
                MeshGL& mesh = m_meshes.get(staticmesh.mesh);

                glUniformMatrix4fv(m_wireframePassData.transformLocation, 1, GL_FALSE, staticmesh.transform->getWorldMatrix().data());

                glBindVertexArray(mesh.vao);
                glDrawArrays(GL_TRIANGLES, 0, mesh.size);
                glBindVertexArray(0);
            }
        }
    }

    glUseProgram(0);
}
void RendererGL::terminateWireframe() noexcept
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    Engine::assets().shader.unload("renderergl_shader_wireframe");
}