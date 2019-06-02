#pragma once

#include <OpenGL/Export.hpp>
#include <OpenGL/Renderer/RenderPass/RenderPass.hpp>
#include <OpenGL/Renderer/FrameBuffer/RenderBuffer.hpp>
#include <OpenGL/Renderer/FrameBuffer/ForwardPlusBuffers.hpp>
#include <OpenGL/Renderer/Shader/ShaderGLSL.hpp>

#include <Core/Math/Matrix.hpp>

#include <memory>

namespace ax
{
    class AXION_GL_API ForwardPlusPass : public RenderPass
    {
    public:
        ForwardPlusPass(RenderContent& content, RendererGUIViewportGL& viewport, bool lightCullingDebug = false);

        void onInitialize(const Vector2u& resolution) noexcept override;
        void onTerminate() noexcept override;
        void onUpdateResolution(const Vector2u& resolution) noexcept override;
        void onRender(const RenderBuffer& renderBuffer, const RendererCameraGL& camera, double alpha) noexcept override;

    private:
        void updateUBOs(const RendererCameraGL& camera) noexcept;
        void renderGeometryPass() noexcept;
        void processCullPass() noexcept;
        void renderLightPass() noexcept;
        void renderPPPass(const RenderBuffer& renderBuffer) noexcept;
        void renderDebug(const RenderBuffer& renderBuffer) noexcept;

    private:
        Matrix4f m_viewMatrix;
        Matrix4f m_vpMatrix;

        GLuint m_quadTextureShader;
        GLuint m_genericShader;
        GLuint m_geometryShader;
        GLuint m_postProcessShader;
        GLuint m_lightCullComputeShader;
        GLuint m_debugLightCullingShader;

        std::unique_ptr<ForwardPlusBuffers> m_buffers;

        Vector2u m_resolution;

        bool m_lightCullingDebug;
    };
}