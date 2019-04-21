#pragma once

#include <OpenGL/Export.hpp>

namespace ax
{
    class AXION_GL_API RendererGUIComponent
    {
    public:
        RendererGUIRectangleHandle addRectangle() override;
        void removeRectangle(RendererGUIRectangleHandle& handle) override;

        RendererGUIScalableRectangleHandle addScalableRectangle() override;
        void removeScalableRectangle(RendererGUIScalableRectangleHandle& handle) override;

    public:
        void draw();
        virtual void onDraw() = 0;

    private:
        IndexVector<std::unique_ptr<RendererGUIRectangleGL>> rectangles;
        IndexVector<std::unique_ptr<RendererGUIRectangleGL>> scalableRectangles;
    };
}