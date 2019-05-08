#pragma once

#include <OpenGL/Export.hpp>
#include <OpenGL/Renderer/RenderPass/RenderPass.hpp>
#include <OpenGL/Renderer/FrameBuffer/RenderBuffer.hpp>

#include <OpenGL/Renderer/GUI/RendererGUILayoutGL.hpp>

#include <memory>

namespace ax
{
    class AXION_GL_API WireframePass : public RenderPass
    {
    public:
        WireframePass(RenderContent& content, RendererGUIViewportGL& viewport);

        void initialize() noexcept override;
        void terminate() noexcept override;
        void updateResolution() noexcept override;
        void render(double alpha) noexcept override;

    private:
        std::unique_ptr<RenderBuffer> m_renderBuffer;

        GLuint m_quadTextureShader;
        GLuint m_wireframeShader;
        GLuint m_guiRectangleShader;

        std::unique_ptr<RendererGUILayoutGL> m_layout;
    };
}