#pragma once

#include <OpenGL/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Utility/Color.hpp>
#include <Core/Renderer/RendererMaterialParameters.hpp>

namespace ax
{
    struct AXION_GL_API MaterialGL
    {
        RendererMaterialParameters parameters;

        GLuint uboIndex;
    };
}