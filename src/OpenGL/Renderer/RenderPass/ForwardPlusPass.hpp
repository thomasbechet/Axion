#pragma once

//////////////
//HEADERS
//////////////
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
        ForwardPlusPass(RenderContent& content, Viewport& viewport);

        void initialize() noexcept override;
        void terminate() noexcept override;
        void updateResolution() noexcept override;
        void render(double alpha) noexcept override;

    private:
        void updateUBOs() noexcept;
        void renderGeometryPass() noexcept;
        void processCullPass() noexcept;
        void renderLightPass() noexcept;
        void renderPPPass() noexcept;
        void renderViewportPass() noexcept;

    private:
        Matrix4f m_viewMatrix;
        Matrix4f m_vpMatrix;

    private:
        GLuint m_quadTextureShader;
        GLuint m_genericShader;
        GLuint m_geometryShader;
        GLuint m_postProcessShader;
        GLuint m_lightCullComputeShader;

        std::unique_ptr<RenderBuffer> m_renderBuffer;
        std::unique_ptr<ForwardPlusBuffers> m_buffers;
    };
}