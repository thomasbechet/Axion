#pragma once

#include <OpenGL/Export.hpp>
#include <OpenGL/Renderer/GUI/RendererGUIComponentGL.hpp>
#include <Core/Renderer/GUI/RendererGUIScalableRectangle.hpp>

namespace ax
{
    class AXION_GL_API RendererGUIScalableRectangleGL : public RendererGUIScalableRectangle, RendererGUIComponentGL
    {
    public:
        RendererGUIScalableRectangleGL();
        ~RendererGUIScalableRectangleGL();

        void setTransform(Transform2D* transform) override;
        void setVisible(bool toggle) override;
        void setTransparency(float transparency) override;
        void setColor(Color3 color) override;
        void setDepth(unsigned depth) override;

        void draw() noexcept;
    };
}