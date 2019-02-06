#pragma once

//////////////
//HEADERS
//////////////
#include <OpenGL/Export.hpp>
#include <OpenGL/Renderer/RenderPass/RenderPass.hpp>
#include <OpenGL/Renderer/FrameBuffer/RenderBuffer.hpp>
#include <OpenGL/Renderer/FrameBuffer/ForwardPlusBuffers.hpp>
#include <OpenGL/Renderer/Utility/ShaderGLSL.hpp>

#include <Core/Math/Matrix.hpp>

#include <memory>

namespace ax
{
    class AXION_GL_API DebugLightCullingPass : public RenderPass
    {
    public:
        DebugLightCullingPass(RenderContent& content, Viewport& viewport);

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
        void initializeCullPass() noexcept;
        void terminateCullPass() noexcept;
        std::unique_ptr<ShaderGLSL> m_cullingShader;
        GLuint m_cullSSBO;
        Vector2u workGroupSize;

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
        GLuint m_debugLightCullingShader;
        GLuint m_geometryShader;

        std::unique_ptr<RenderBuffer> m_renderBuffer;
        std::unique_ptr<ForwardPlusBuffers> m_buffers;
    };
}