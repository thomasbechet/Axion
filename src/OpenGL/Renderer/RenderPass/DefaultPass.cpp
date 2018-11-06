#include <OpenGL/Renderer/RendererGL.hpp>

#include <OpenGL/Renderer/RendererGL.hpp>
#include <Core/Context/Engine.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Assets/AssetManager.hpp>

using namespace ax;

DefaultPass::DefaultPass(RenderContent& content) : RenderPass(content) {}

void DefaultPass::initialize() noexcept
{
    //Engine::assets().shader.load()

    glClearColor(content.clearColor.r, content.clearColor.g, content.clearColor.b, content.clearColor.a);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
}
void DefaultPass::terminate() noexcept
{

}
void DefaultPass::updateViewport() noexcept
{
    glViewport(0, 0, content.windowSize.x, content.windowSize.y);
}
void DefaultPass::render(double alpha) noexcept
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ShaderGL& shader = content.shaders.get(1);
    glUseProgram(shader.programId);

    CameraGL& camera = content.cameras.get(1);

    int viewLocation = glGetUniformLocation(shader.programId, "camera_view");
    int projectionLocation = glGetUniformLocation(shader.programId, "camera_projection");

    Vector3f eye = camera.transform->getTranslation();
    Vector3f target = camera.transform->getTranslation() + camera.transform->getForwardVector();
    Vector3f up = camera.transform->getUpVector();

    Matrix4f viewMatrix = Matrix4f::lookAt(eye, target, up);
    Matrix4f projectionMatrix = Matrix4f::perspective(camera.fov, (float)Engine::window().getSize().x / (float)Engine::window().getSize().y, camera.near, camera.far);

    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, viewMatrix.data());
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, projectionMatrix.data());

    for(auto& materialIt : content.materials)
    {
        MaterialGL& material = materialIt.first;

        if(material.useDiffuseTexture)
        {
            glUniform1i(glGetUniformLocation(shader.programId, "useDiffuse"), true);

            int textureLocation = glGetUniformLocation(shader.programId, "texture");
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, content.textures.get(material.diffuseTexture).id);
        }
        else
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glUniform1i(glGetUniformLocation(shader.programId, "useDiffuse"), false);   
        }

        for(auto& staticmeshId : materialIt.second)
        {
            StaticmeshGL& staticmesh = content.staticmeshes.get(staticmeshId);
            if(staticmesh.mesh)
            {
                MeshGL& mesh = content.meshes.get(staticmesh.mesh);

                int transformLocation = glGetUniformLocation(shader.programId, "transform");
                glUniformMatrix4fv(transformLocation, 1, GL_TRUE, staticmesh.transform->getWorldMatrix().data());

                glBindVertexArray(mesh.vao);
                glDrawArrays(GL_TRIANGLES, 0, mesh.size);
                glBindVertexArray(0);
            }
        }
    }

    glUseProgram(0);
}