#pragma once

#include <Core/Export.hpp>
#include <Core/Renderer/Asset/RendererTexture.hpp>
#include <Core/Renderer/Asset/RendererShader.hpp>
#include <Core/Math/Transform2D.hpp>
#include <Core/Utility/Color.hpp>

namespace ax
{
    struct AXION_CORE_API RendererGUIRectangleParameters
    {
        unsigned width = 0;
        unsigned height = 0;

        unsigned uvLeft = 0;
        unsigned uvRight = 0;
        unsigned uvTop = 0;
        unsigned uvBottom = 0;

        RendererTextureHandle texture = nullptr;
        RendererShaderHandle shader = nullptr;
    };

    class AXION_CORE_API RendererGUIRectangle
    {
    public:
        virtual void setTransform(Transform2D* transform) = 0;
        virtual void setVisible(bool toggle) = 0;
        virtual void setTransparency(float transparency) = 0;
        virtual void setColor(Color3 color) = 0;
        virtual void setDepth(unsigned depth) = 0;
        virtual void setParameters(const RendererGUIRectangleParameters& parameters) = 0;
    };

    class AXION_CORE_API NullRendererGUIRectangle : public RendererGUIRectangle
    {
    public:
        void setTransform(Transform2D* transform) override {}
        void setVisible(bool toggle) override {}
        void setTransparency(float transparency) override {}
        void setColor(Color3 color) override {}
        void setDepth(unsigned depth) override {}
        void setParameters(const RendererGUIRectangleParameters& parameters) override {}
    };

    using RendererGUIRectangleHandle = RendererGUIRectangle*;
}