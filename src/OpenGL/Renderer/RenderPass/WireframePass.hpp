#pragma once

#include <OpenGL/Export.hpp>
#include <OpenGL/Renderer/RenderPass/RenderPass.hpp>
#include <OpenGL/Renderer/FrameBuffer/RenderBuffer.hpp>

#include <memory>

namespace ax
{
    class AXION_GL_API WireframePass : public RenderPass
    {
    public:
        WireframePass(RenderContent& content);

        void onInitialize(const Vector2u& resolution) noexcept override;
        void onTerminate() noexcept override;
        void onUpdateResolution(const Vector2u& resolution) noexcept override;
        void onRender(RenderBuffer& renderBuffer, RendererCameraGL& camera, double alpha) noexcept override;

    private:
        GLuint m_quadTextureShader;
        GLuint m_wireframeShader;
        GLuint m_guiRectangleShader;
    };
}