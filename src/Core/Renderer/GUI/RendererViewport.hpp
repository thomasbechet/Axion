#pragma once

#include <Core/Export.hpp>
#include <Core/Math/Vector.hpp>
#include <Core/Renderer/RenderMode.hpp>
#include <Core/Renderer/Scene/RendererCamera.hpp>

namespace ax
{
    class AXION_CORE_API RendererViewport
    {
    public:
        virtual void setRendermode(RenderMode mode) = 0;
        virtual void setCamera(RendererCameraHandle camera) = 0;
        virtual void setResolution(const Vector2u& resolution) = 0;
        virtual void setRectangle(const Vector2f& position, const Vector2f& size) = 0;
    };

    class AXION_CORE_API NullRendererViewport : public RendererViewport
    {
    public:
        void setRendermode(RenderMode mode) override {}
        void setCamera(RendererCameraHandle camera) override {}
        void setResolution(const Vector2u& resolution) override {}
        void setRectangle(const Vector2f& position, const Vector2f& size) override {}
    };

    using RendererViewportHandle = RendererViewport*;
}