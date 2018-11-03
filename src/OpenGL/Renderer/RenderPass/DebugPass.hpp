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

    class AXION_GL_API DebugPass : public RenderPass
    {
    public:
        DebugPass(RenderContent& content);

        void initialize() noexcept override;
        void terminate() noexcept override;
        void updateViewport() noexcept override;
        void render(double alpha) noexcept override;

    private:
        GLuint m_geometryShader;
        GLuint m_debugShader;

        GLuint m_viewLocation;
        GLuint m_projectionLocation;
        GLuint m_transformLocation;

        GLuint m_materialIndexLocation;
        GLuint m_diffuseTextureLocation;
        GLuint m_normalTextureLocation;
        GLuint m_specularTextureLocation;

        std::unique_ptr<GBuffer> m_gbuffer;
    };
}