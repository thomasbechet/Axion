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
        bool useDiffuseColor;
        Color3 diffuseColor;
        Id diffuseTexture;

        bool useNormalTexture;
        bool isBumpTexture;
        Id normalTexture;

        bool useSpecularTexture;
        float specularUniform;
        Id specularTexture;

        GLuint uboIndex;
    };
}