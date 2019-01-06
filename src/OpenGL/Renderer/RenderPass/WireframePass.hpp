#pragma once

//////////////
//HEADERS
//////////////
#include <OpenGL/Export.hpp>
#include <OpenGL/Renderer/RenderPass/RenderPass.hpp>

namespace ax
{
    class RenderContent;

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
    };
}