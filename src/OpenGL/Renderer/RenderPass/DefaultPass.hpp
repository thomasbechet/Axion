#pragma once

//////////////
//HEADERS
//////////////
#include <OpenGL/Export.hpp>
#include <OpenGL/Renderer/RenderPass/RenderPass.hpp>

#include <memory>

namespace ax
{
    class RenderContent;

    class AXION_GL_API DefaultPass : public RenderPass
    {
    public:
        DefaultPass(RenderContent& content);

        void initialize() noexcept override;
        void terminate() noexcept override;
        void updateViewport() noexcept override;
        void render(double alpha) noexcept override;

    private:
        GLuint m_geometryShader;
        GLuint m_lightShader;

        GLuint m_viewLocation;
        GLuint m_projectionLocation;
        GLuint m_transformLocation;

        std::unique_ptr<GBuffer> m_gbuffer;
    };
}