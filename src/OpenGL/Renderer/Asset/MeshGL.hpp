#pragma once

#include <OpenGL/Export.hpp>

#include <GL/glew.h>

namespace ax
{
    struct AXION_GL_API MeshGL
    {
        GLuint vao;
        GLuint vbo;
        size_t size;
    };
}