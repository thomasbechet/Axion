#pragma once

//////////////
//HEADERS
//////////////
#include <OpenGL/Export.hpp>
#include <OpenGL/Renderer/RenderPass/RenderPass.hpp>
#include <OpenGL/Renderer/FrameBuffer/RenderBuffer.hpp>

#include <memory>

namespace ax
{
    class RenderContent;

    class AXION_GL_API DefaultPass : public RenderPass
    {
    public:
        DefaultPass(RenderContent& content, Viewport& viewport);

        void initialize() noexcept override;
        void terminate() noexcept override;
        void updateResolution() noexcept override;
        void render(double alpha) noexcept override;

    private:
        GLuint m_transformLocation;
        GLuint m_mvpLocation;
        GLuint m_v;
        GLuint m_p;

        GLuint m_materialIndexLocation;
        GLuint m_diffuseTextureLocation;
        GLuint m_normalTextureLocation;
        GLuint m_specularTextureLocation;

        GLuint m_pointLightIndexLocation;
        GLuint m_pointLightPositionLocation;

        std::unique_ptr<GBuffer> m_gbuffer;
        std::unique_ptr<RenderBuffer> m_renderBuffer;
    };
}