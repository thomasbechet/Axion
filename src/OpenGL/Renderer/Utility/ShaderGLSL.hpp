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
    class AXION_GL_API ShaderGLSL
    {
    public:
        ~ShaderGLSL();

        bool loadShader(const std::string* vertex = nullptr, const std::string* fragment = nullptr) noexcept;
        bool loadCompute(const std::string& compute) noexcept;
        bool loadCompute(const Path path) noexcept;

        bool isLoaded() const noexcept;
        GLuint getProgram() const noexcept;

    private:
        void injectHeaders(std::string& code) noexcept;

        bool m_isLoaded = false;
        GLuint m_handle;
    };
}