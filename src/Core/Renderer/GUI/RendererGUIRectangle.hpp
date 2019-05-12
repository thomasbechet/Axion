#pragma once

#include <Core/Export.hpp>
#include <Core/Renderer/GUI/RendererGUIComponent.hpp>
#include <Core/Renderer/Asset/RendererTexture.hpp>
#include <Core/Renderer/Asset/RendererShader.hpp>
#include <Core/Math/Rect.hpp>

namespace ax
{
    class AXION_CORE_API RendererGUIRectangle : public RendererGUIComponent
    {
    public:
        virtual void setSize(Vector2u size) = 0;
        virtual void setOrigin(Vector2i origin) = 0;
        virtual void setUV(Rectu uv) = 0;
        virtual void setTexture(RendererTextureHandle texture) = 0;
        virtual void setShader(RendererShaderHandle shader) = 0;
    };

    class AXION_CORE_API NullRendererGUIRectangle : public RendererGUIRectangle
    {
    public:
        void setTransform(Transform2D* transform) override {}
        void setVisible(bool toggle) override {}
        void setTransparency(float transparency) override {}
        void setColor(Color3 color) override {}
        void setDepth(int depth) override {}

        void setSize(Vector2u size) override {}
        void setOrigin(Vector2i origin) override {}
        void setUV(Rectu uv) override {}
        void setTexture(RendererTextureHandle texture) override {}
        void setShader(RendererShaderHandle shader) override {}
    };

    using RendererGUIRectangleHandle = RendererGUIRectangle*;
}