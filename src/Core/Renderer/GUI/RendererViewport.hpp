#pragma once

#include <Core/Export.hpp>
#include <Core/Math/Vector.hpp>
#include <Core/Renderer/RenderMode.hpp>
#include <Core/Renderer/Scene/RendererCamera.hpp>

namespace ax
{
    using RendererViewportPointer = RendererViewport*;

    class AXION_CORE_API RendererViewport
    {
    public:
        virtual void setRendermode(RenderMode mode) = 0;
        virtual void setCamera(RendererCameraPointer camera) = 0;
        virtual void setResolution(const Vector2u& resolution) = 0;
        virtual void setRectangle(const Vector2f& position, const Vector2f& size) = 0;
    };
}