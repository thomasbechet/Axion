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
        bool loadShader(const std::string* vertex = nullptr, const std::string* fragment = nullptr) noexcept;
        bool loadCompute(const std::string& compute) noexcept;
        void unload() noexcept;

        bool isLoaded() const noexcept;
        GLuint getProgram() const noexcept;

    private:
        bool compileShader(const std::string& vertex, const std::string& fragment) noexcept;
        bool compileCompute(const std::string& compute) noexcept;
        void injectConstants(std::string& code) noexcept;
        void replaceConstantInteger(std::string& code, int value, std::string name) noexcept;

        bool m_isLoaded = false;
        GLuint m_handle;
    };
}