#include <OpenGL/Renderer/RendererGL.hpp>

#include <Core/Renderer/RendererException.hpp>

#include <tuple>

using namespace ax;

Id RendererGL::createMesh(const std::vector<Vertex>& vertices)
{
    Id id = m_meshes.add(MeshGL());
    MeshGL& mesh = m_meshes.get(id);
    mesh.size = vertices.size();

    glGenVertexArrays(1, &mesh.vao);
    glBindVertexArray(mesh.vao);

    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(Vector3f)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(Vector3f) + sizeof(Vector2f)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(Vector3f) + sizeof(Vector2f) + sizeof(Vector3f)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(4, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(Vector3f) + sizeof(Vector2f) + sizeof(Vector3f) + sizeof(Vector3f)));
    glEnableVertexAttribArray(4);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return id;
}
void RendererGL::destroyMesh(Id id)
{
    MeshGL& mesh = m_meshes.get(id);

    glDeleteVertexArrays(1, &mesh.vao);
    glDeleteBuffers(1, &mesh.vbo);

    m_meshes.remove(id);
}