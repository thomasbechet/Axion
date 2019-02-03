#pragma once

//////////////
//HEADERS
//////////////
#include <OpenGL/Export.hpp>
#include <OpenGL/Renderer/RenderPass/RenderPass.hpp>
#include <OpenGL/Renderer/FrameBuffer/RenderBuffer.hpp>
#include <OpenGL/Renderer/FrameBuffer/ForwardPlusBuffers.hpp>
#include <OpenGL/Renderer/Utility/ShaderHolder.hpp>

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
        void initializeCullPass() noexcept;
        void terminateCullPass() noexcept;
        std::unique_ptr<ShaderHolder> m_cullingShader;
        GLuint m_cullSSBO;

    private:
        Matrix4f m_viewMatrix;
        Matrix4f m_vpMatrix;

    private:
        struct PhongLocations
        {
            GLuint transform;
            GLuint mvp;
            GLuint normalToView;

            GLuint materialIndex;
            GLuint diffuseTexture;
            GLuint normalTexture;
        };

        PhongLocations phongLocations;
        
        struct GeometryLocations
        {
            GLuint transform;
            GLuint mvp;
            GLuint normalToView;

            GLuint materialIndex;
            GLuint normalTexture;
        };

        GeometryLocations geometryLocations;

    private:
        GLuint m_phongShader;
        GLuint m_geometryShader;

        std::unique_ptr<RenderBuffer> m_renderBuffer;
        std::unique_ptr<ForwardPlusBuffers> m_buffers;
    };
}