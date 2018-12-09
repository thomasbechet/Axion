#pragma once

////////////
//HEADERS
////////////
#include <OpenGL/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Utility/Color.hpp>

namespace ax
{
    struct AXION_GL_API MaterialGL
    {
        bool useDiffuseTexture;
        Color diffuseColor;
        Id diffuseTexture;

        bool useNormalTexture;
        bool isBumpTexture;
        Id normalTexture;

        GLuint uboIndex;
    };
}