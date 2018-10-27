#include <OpenGL/Renderer/RendererGL.hpp>

using namespace ax;

void RendererGL::initializeWireframe() noexcept
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
void RendererGL::renderWireframe(double alpha) noexcept
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    

    for(auto& materialIt : m_materials)
    {
        for(auto& staticmeshId : materialIt.second)
        {
            StaticmeshGL& staticmesh = m_staticmeshes.get(staticmeshId);
            if(staticmesh.mesh)
            {
                MeshGL& mesh = m_meshes.get(staticmesh.mesh);

                int transformLocation = glGetUniformLocation(shader.programId, "transform");
                glUniformMatrix4fv(transformLocation, 1, GL_FALSE, staticmesh.transform->getWorldMatrix().data());

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
}