#pragma once

#include <OpenGL/Export.hpp>
#include <OpenGL/Renderer/GUI/RendererGUIRectangleGL.hpp>
#include <OpenGL/Renderer/GUI/RendererGUIScalableRectangleGL.hpp>
#include <Core/Renderer/GUI/RendererGUILayout.hpp>
#include <Core/Utility/IndexVector.hpp>

#include <memory>

namespace ax
{
    class AXION_GL_API RendererGUILayoutGL : public RendererGUILayout
    {
    public:
        RendererGUIRectangleHandle createRectangle() override;
        void destroyRectangle(RendererGUIRectangleHandle& handle) override;

        RendererGUIScalableRectangleHandle createScalableRectangle() override;
        void destroyScalableRectangle(RendererGUIScalableRectangleHandle& handle) override;

        

        IndexVector<std::unique_ptr<RendererGUIRectangleGL>> rectangles;
        IndexVector<std::unique_ptr<RendererGUIRectangleGL>> scalableRectangles;
    };
}