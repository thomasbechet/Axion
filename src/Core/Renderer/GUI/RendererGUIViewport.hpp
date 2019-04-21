#pragma once

#include <Core/Export.hpp>
#include <Core/Math/Vector.hpp>
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
        virtual void setRectangle(const Vector2f& position, const Vector2f& size) = 0;
    };

    class AXION_CORE_API NullRendererGUIViewport : public RendererGUIViewport
    {
    public:
        void setRendermode(RenderMode mode) override {}
        void setCamera(RendererCameraHandle camera) override {}
        void setResolution(const Vector2u& resolution) override {}
        void setRectangle(const Vector2f& position, const Vector2f& size) override {}
    };

    using RendererGUIViewportHandle = RendererGUIViewport*;
}