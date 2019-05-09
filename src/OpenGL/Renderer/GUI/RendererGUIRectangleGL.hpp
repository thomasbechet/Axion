#pragma once

#include <OpenGL/Export.hpp>
#include <OpenGL/Renderer/GUI/RendererGUIComponentGL.hpp>
#include <Core/Renderer/GUI/RendererGUIRectangle.hpp>
#include <Core/Utility/Types.hpp>

#include <GL/glew.h>

namespace ax
{
    class AXION_GL_API RendererGUIRectangleGL : public RendererGUIRectangle, public RendererGUIComponentGL
    {
    public:
        RendererGUIRectangleGL(RendererGUILayoutGL& layout, GLuint defaultShader);
        ~RendererGUIRectangleGL();

        void setTransform(Transform2D* transform) override;
        void setVisible(bool toggle) override;
        void setTransparency(float transparency) override;
        void setColor(Color3 color) override;
        void setDepth(unsigned depth) override;
        
        void setSize(Vector2u size) override;
        void setOrigin(Vector2i origin) override;
        void setUV(Rectu uv) override;
        void setTexture(RendererTextureHandle texture) override;
        void setShader(RendererShaderHandle shader) override;

        void draw() noexcept override;

    private:
        Transform2D* m_transform = nullptr;
        bool m_visible = true;
        Color3 m_color;
        unsigned m_depth = 0;
        float m_transparency = 0.0f;

        Vector2u m_size;
        Vector2i m_origin;
        Rectu m_uv;
        RendererTextureHandle m_texture = nullptr;
        RendererShaderHandle m_shader = nullptr;

        GLuint m_vao;
        GLuint m_ibo;
        GLuint m_uvVBO;
        GLuint m_positionVBO;
        GLuint m_defaultShader;

    private:
        void create() noexcept;
        void destroy() noexcept;
        void updatePositions() noexcept;
        void updateUVs() noexcept;
    };
}