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
        WireframePass(RenderContent& content);

        void initialize() noexcept override;
        void terminate() noexcept override;
        void updateViewport() noexcept override;
        void render(double alpha) noexcept override;

    private:
        GLuint m_shader;
        GLuint m_viewLocation;
        GLuint m_projectionLocation;
        GLuint m_transformLocation;
    };
}