#pragma once

//////////////
//HEADERS
//////////////
#include <OpenGL/Export.hpp>

#include <memory>

namespace ax
{
    struct AXION_GL_API DebugPassData
    {
        GLuint geometryShader;
        GLuint debugShader;

        GLuint viewLocation;
        GLuint projectionLocation;
        GLuint transformLocation;

        GLuint materialIndexLocation;
        GLuint diffuseTextureLocation;
        GLuint normalTextureLocation;
        GLuint specularTextureLocation;

        std::unique_ptr<GBuffer> gbuffer;
    };
}