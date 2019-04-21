#pragma once

#include <OpenGL/Export.hpp>
#include <Core/Renderer/GUI/RendererGUIRectangle.hpp>
#include <Core/Utility/Types.hpp>

namespace ax
{
    class AXION_GL_API RendererGUIRectangleGL : public RendererGUIRectangle
    {
    public:
        void setTransform(Transform2D* transform) override;
        void setVisible(bool toggle) override;
        void setTransparency(float transparency) override;
        void setColor(Color3 color) override;
        void setDepth(unsigned depth) override;
        void setParameters(const RendererGUIRectangleParameters& parameters) override;

        Transform2D* transform = nullptr;
        bool visible = true;
        Color3 color;
        unsigned depth;
        float transparency = 0.0f;
        RendererGUIRectangleParameters parameters;

        GLuint vao;
        GLuint vbo;

        Id id;
    };
}