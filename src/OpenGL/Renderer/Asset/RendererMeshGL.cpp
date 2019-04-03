#include <OpenGL/Renderer/RendererGL.hpp>

using namespace ax;

void RendererMeshGL::update(const std::vector<Vertex>& vertices)
{
    size = vertices.size();

    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}