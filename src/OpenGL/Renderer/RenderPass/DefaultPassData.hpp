#pragma once

//////////////
//HEADERS
//////////////
#include <OpenGL/Export.hpp>

namespace ax
{
    struct AXION_GL_API DefaultPassData
    {
        GLuint geometryShader;
        GLuint lightShader;

        GLuint viewLocation;
        GLuint projectionLocation;
        GLuint transformLocation;

        std::unique_ptr<GBuffer> gbuffer;
    };
}