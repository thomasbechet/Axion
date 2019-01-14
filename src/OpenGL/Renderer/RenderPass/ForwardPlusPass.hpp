#pragma once

//////////////
//HEADERS
//////////////
#include <OpenGL/Export.hpp>
#include <OpenGL/Renderer/RenderPass/RenderPass.hpp>
#include <OpenGL/Renderer/FrameBuffer/RenderBuffer.hpp>
#include <OpenGL/Renderer/FrameBuffer/ForwardPlusBuffers.hpp>
#include <OpenGL/Renderer/Utility/ComputeShader.hpp>

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
        void renderLightPass() noexcept;
        void renderPPPass() noexcept;
        void renderViewportPass() noexcept;

    private:
        Matrix4f m_viewMatrix;
        Matrix4f m_vpMatrix;

    private:
        GLuint m_transformLocation;
        GLuint m_mvpLocation;
        GLuint m_normalToViewLocation;

        GLuint m_materialIndexLocation;
        GLuint m_diffuseTextureLocation;
        GLuint m_normalTextureLocation;
        GLuint m_specularTextureLocation;

    private:
        GLuint m_phongShader;
        GLuint m_geometryShader;

        std::unique_ptr<RenderBuffer> m_renderBuffer;
        std::unique_ptr<ForwardPlusBuffers> m_buffers;
        std::unique_ptr<ComputeShader> m_cullingShader;
    };
}