#pragma once

#include <Core/Export.hpp>
#include <Core/Renderer/Asset/RendererTexture.hpp>
#include <Core/Renderer/Asset/RendererShader.hpp>
#include <Core/Math/Transform2D.hpp>
#include <Core/Utility/Color.hpp>
#include <Core/Utility/Types.hpp>

namespace ax
{
    struct AXION_CORE_API RendererGUIScalableRectangleParameters
    {
        bool drawBorder = true;
        bool drawInside = true;
        bool roundedCorner = false;

        unsigned width = 0;
        unsigned height = 0;

        unsigned marginLeft = 0;
        unsigned marginRight = 0;
        unsigned marginTop = 0;
        unsigned marginBottom = 0;  

        unsigned uvInsideLeft = 0;
        unsigned uvInsideRight = 0;
        unsigned uvInsideTop = 0;
        unsigned uvInsideBottom = 0;

        unsigned uvBorderLeft = 0;
        unsigned uvBorderRight = 0;
        unsigned uvBorderTop = 0;
        unsigned uvBorderBottom = 0;

        RendererTextureHandle texture = nullptr;
        RendererShaderHandle shader = nullptr;
    };

    class AXION_CORE_API RendererGUIScalableRectangle
    {
    public:
        virtual void setTransform(Transform2D* transform) = 0;
        virtual void setVisible(bool toggle) = 0;
        virtual void setTransparency(float transparency) = 0;
        virtual void setColor(Color3 color) = 0;
        virtual void setDepth(unsigned depth) = 0;
        virtual void setParameters(const RendererGUIScalableRectangleParameters& parameters) = 0;
    };

    class AXION_CORE_API NullRendererGUIScalableRectangle : public RendererGUIScalableRectangle
    {
    public:
        void setTransform(Transform2D* transform) override {}
        void setVisible(bool toggle) override {}
        void setTransparency(float transparency) override {}
        void setColor(Color3 color) override {}
        void setDepth(unsigned depth) override {}
        void setParameters(const RendererGUIScalableRectangleParameters& parameters) override {}
    };

    using RendererGUIScalableRectangleHandle = RendererGUIScalableRectangle*;
}