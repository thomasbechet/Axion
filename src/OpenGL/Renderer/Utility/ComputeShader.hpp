#pragma once

///////////////
//HEADERS
///////////////
#include <OpenGL/Export.hpp>
#include <Core/Utility/Path.hpp>

#include <GL/glew.h>

#include <string>

namespace ax
{
    class AXION_GL_API ComputeShader
    {
    public:
        ComputeShader(std::string code);
        ComputeShader(Path file);
        ~ComputeShader();

        void use() noexcept;

    private:
        void load(std::string code) noexcept;
        void unload() noexcept;

        GLuint m_id;
    };
}