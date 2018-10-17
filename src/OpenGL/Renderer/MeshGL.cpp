#include <OpenGL/Renderer/RendererGL.hpp>

#include <Core/Renderer/RendererException.hpp>

#include <tuple>

using namespace ax;

Id RendererGL::createMesh(const std::vector<Vertex>& vertices)
{
    Id id = m_meshes.add(MeshGL());
    MeshGL& mesh = m_meshes.get(id);
    mesh.size = vertices.size();

    for(auto& vert : vertices)
        std::cout << vert.normal.x << " " << vert.normal.y << std::endl;

    glGenVertexArrays(1, &mesh.vao);
    glBindVertexArray(mesh.vao);

    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(Vector3f)));
    glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(Vector3f) + sizeof(Vector2f)));
    glVertexAttribPointer(3, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(Vector3f) + sizeof(Vector2f) + sizeof(Vector3f)));
    glVertexAttribPointer(4, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(Vector3f) + sizeof(Vector2f) + sizeof(Vector3f) + sizeof(Vector3f)));

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