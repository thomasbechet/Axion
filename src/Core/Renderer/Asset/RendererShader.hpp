#pragma once

#include <Core/Export.hpp>

namespace ax
{
    class AXION_CORE_API RendererShader
    {
    public:
    };

    class AXION_CORE_API NullRendererShader : public RendererShader
    {
    public:
    };

    using RendererShaderHandle = RendererShader*;
}