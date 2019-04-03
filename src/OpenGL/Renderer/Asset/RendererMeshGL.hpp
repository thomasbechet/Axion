#pragma once

#include <OpenGL/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Renderer/Asset/RendererMesh.hpp>

#include <GL/glew.h>

namespace ax
{
    class AXION_GL_API RendererMeshGL : public RendererMesh
    {
    public:
        void update(const std::vector<Vertex>& vertices) override;

        GLuint vao;
        GLuint vbo;
        size_t size;

        Id id;
    };
}