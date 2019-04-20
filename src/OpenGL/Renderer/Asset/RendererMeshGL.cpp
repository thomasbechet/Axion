#include <OpenGL/Renderer/RendererGL.hpp>

using namespace ax;

RendererMeshHandle RendererGL::createMesh(const std::vector<Vertex>& vertices)
{
    Id id = m_content.meshes.add(std::make_unique<RendererMeshGL>());
    RendererMeshGL* mesh = m_content.meshes.get(id).get();
    mesh->id = id;

    glGenVertexArrays(1, &mesh->vao);
    glBindVertexArray(mesh->vao);

    glGenBuffers(1, &mesh->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(Vector3f)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(Vector3f) + sizeof(Vector2f)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(Vector3f) + sizeof(Vector2f) + sizeof(Vector3f)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(4, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(Vector3f) + sizeof(Vector2f) + sizeof(Vector3f) + sizeof(Color3)));
    glEnableVertexAttribArray(4);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    mesh->update(vertices);

    return mesh;
}
void RendererGL::destroyMesh(RendererMeshHandle& meshPointer)
{
    RendererMeshGL* mesh = static_cast<RendererMeshGL*>(meshPointer);
    glDeleteVertexArrays(1, &mesh->vao);
    glDeleteBuffers(1, &mesh->vbo);
    m_content.meshes.remove(mesh->id);
    meshPointer = nullptr;
}

void RendererMeshGL::update(const std::vector<Vertex>& vertices)
{
    size = vertices.size();

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}