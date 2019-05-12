#pragma once

#include <OpenGL/Export.hpp>
#include <OpenGL/Renderer/GUI/RendererGUIComponentGL.hpp>
#include <OpenGL/Renderer/GUI/RendererGUILayoutGL.hpp>
#include <Core/Renderer/GUI/RendererGUIScalableRectangle.hpp>

namespace ax
{
    class AXION_GL_API RendererGUIScalableRectangleGL : public RendererGUIScalableRectangle, public RendererGUIComponentGL
    {
    public:
        RendererGUIScalableRectangleGL(RendererGUILayoutGL& layout, GLuint defaultShader);
        ~RendererGUIScalableRectangleGL();

        void setTransform(Transform2D* transform) override;
        void setVisible(bool toggle) override;
        void setTransparency(float transparency) override;
        void setColor(Color3 color) override;
        void setDepth(int depth) override;

        void draw() noexcept;

    private:
        GLuint m_defaultShader;
    };
}