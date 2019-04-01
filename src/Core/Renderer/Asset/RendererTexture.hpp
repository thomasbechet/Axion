#pragma once

#include <Core/Export.hpp>

namespace ax
{
    class AXION_CORE_API RendererTexture
    {
    public:
    };

    class AXION_CORE_API NullRendererTexture : public RendererTexture
    {
    public:
    };

    using RendererTextureHandle = RendererTexture*;
}