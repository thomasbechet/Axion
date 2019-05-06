#pragma once

#include <OpenGL/Export.hpp>
#include <OpenGL/Renderer/GUI/RendererGUIComponentGL.hpp>
#include <Core/Renderer/GUI/RendererGUIRectangle.hpp>
#include <Core/Utility/Types.hpp>

#include <GL/glew.h>

namespace ax
{
    class AXION_GL_API RendererGUIRectangleGL : public RendererGUIRectangle, RendererGUIComponentGL
    {
    public:
        RendererGUIRectangleGL();
        ~RendererGUIRectangleGL();

        void setTransform(Transform2D* transform) override;
        void setVisible(bool toggle) override;
        void setTransparency(float transparency) override;
        void setColor(Color3 color) override;
        void setDepth(unsigned depth) override;
        void setParameters(const RendererGUIRectangleParameters& parameters) override;

        void draw() noexcept override;

        Transform2D* transform = nullptr;
        bool visible = true;
        Color3 color;
        unsigned depth = 0;
        float transparency = 0.0f;
        RendererGUIRectangleParameters parameters;

        GLuint vao;
        GLuint ibo;
        GLuint uvsVBO;
        GLuint positionsVBO;

    private:
        void create() noexcept;
        void update() noexcept;
        void destroy() noexcept;
    };
}