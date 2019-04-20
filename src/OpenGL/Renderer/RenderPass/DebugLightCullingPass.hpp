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
    class AXION_GL_API DebugLightCullingPass : public RenderPass
    {
    public:
        DebugLightCullingPass(RenderContent& content, RendererViewportGL& viewport);

        void initialize() noexcept override;
        void terminate() noexcept override;
        void updateResolution() noexcept override;
        void render(double alpha) noexcept override;

    private:
        void updateUBOs() noexcept;
        void renderGeometryPass() noexcept;
        void processCullPass() noexcept;
        void renderScene() noexcept;
        void renderDebug() noexcept;
        void renderViewportPass() noexcept;

    private:
        std::unique_ptr<ShaderGLSL> m_cullingShader;
        GLuint m_cullSSBO;
        Vector2u workGroupSize;

    private:
        Matrix4f m_viewMatrix;
        Matrix4f m_vpMatrix;

    private:
        std::unique_ptr<RenderBuffer> m_renderBuffer;

        GLuint m_quadTextureShader;
        GLuint m_wireframeShader;
        GLuint m_debugLightCullingShader;
        GLuint m_lightCullComputeShader;
    };
}