#pragma once

#include <Core/Export.hpp>
#include <Core/Math/Vector.hpp>
#include <Core/Math/Rect.hpp>
#include <Core/Renderer/RenderMode.hpp>
#include <Core/Renderer/Scene/RendererCamera.hpp>

namespace ax
{
    class AXION_CORE_API RendererGUIViewport
    {
    public:
        virtual void setRendermode(RenderMode mode) = 0;
        virtual void setCamera(RendererCameraHandle camera) = 0;
        virtual void setResolution(const Vector2u& resolution) = 0;
        virtual void setViewport(const Rectf& rect) = 0; 
    };

    class AXION_CORE_API NullRendererGUIViewport : public RendererGUIViewport
    {
    public:
        void setRendermode(RenderMode mode) override {}
        void setCamera(RendererCameraHandle camera) override {}
        void setResolution(const Vector2u& resolution) override {}
        void setViewport(const Rectf& rect) override {}
    };

    using RendererGUIViewportHandle = RendererGUIViewport*;
}