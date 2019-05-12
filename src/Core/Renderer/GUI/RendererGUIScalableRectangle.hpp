#pragma once

#include <Core/Export.hpp>
#include <Core/Renderer/GUI/RendererGUIComponent.hpp>
#include <Core/Renderer/Asset/RendererTexture.hpp>
#include <Core/Renderer/Asset/RendererShader.hpp>
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

        //REVOIR LE SYSTEME UV

        unsigned marginLeft = 0;
        unsigned marginRight = 0;
        unsigned marginTop = 0;
        unsigned marginBottom = 0;  

        RendererTextureHandle texture = nullptr;
        RendererShaderHandle shader = nullptr;
    };

    class AXION_CORE_API RendererGUIScalableRectangle : public RendererGUIComponent
    {
    public:
        /*virtual void setSize(Vector2u size) = 0;
        //virtual void setMargin
        virtual void setInsideUV(Rectu uv) = 0;
        virtual void setBorderUV(Rectu uv) = 0;
        virtual void setTexture(RendererTextureHandle texture) = 0;
        virtual void setShader(RendererShaderHandle shader) = 0;*/
    };

    class AXION_CORE_API NullRendererGUIScalableRectangle : public RendererGUIScalableRectangle
    {
    public:
        void setTransform(Transform2D* transform) override {}
        void setVisible(bool toggle) override {}
        void setTransparency(float transparency) override {}
        void setColor(Color3 color) override {}
        void setDepth(int depth) override {}
        
        /*virtual void setSize(Vector2u size) override {}
        //virtual void setMargin
        virtual void setInsideUV(Rectu uv) override {}
        virtual void setBorderUV(Rectu uv) override {}
        virtual void setTexture(RendererTextureHandle texture) override {}
        virtual void setShader(RendererShaderHandle shader) override {}*/
    };

    using RendererGUIScalableRectangleHandle = RendererGUIScalableRectangle*;
}