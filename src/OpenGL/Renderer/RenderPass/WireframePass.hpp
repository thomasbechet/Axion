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
    class AXION_GL_API WireframePass : public RenderPass
    {
    public:
        WireframePass(RenderContent& content, Viewport& viewport);

        void initialize() noexcept override;
        void terminate() noexcept override;
        void updateResolution() noexcept override;
        void render(double alpha) noexcept override;

    private:
        GLuint m_mvpLocation;

        std::unique_ptr<RenderBuffer> m_renderBuffer;

        GLuint m_wireframeShader;
    };
}