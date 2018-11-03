#pragma once

/////////////
//HEADERS
/////////////
#include <OpenGL/Export.hpp>
#include <OpenGL/Renderer/TextureGL.hpp>
#include <OpenGL/Renderer/MeshGL.hpp>
#include <OpenGL/Renderer/StaticmeshGL.hpp>
#include <OpenGL/Renderer/MaterialGL.hpp>
#include <OpenGL/Renderer/ShaderGL.hpp>
#include <OpenGL/Renderer/CameraGL.hpp>
#include <OpenGL/Renderer/Light/PointLightGL.hpp>
#include <OpenGL/Renderer/Light/DirectionalLightGL.hpp>
#include <OpenGL/Renderer/GBuffer.hpp>
#include <OpenGL/Renderer/MaterialUBO.hpp>
#include <OpenGL/Renderer/RenderPass/DebugPass.hpp>
#include <OpenGL/Renderer/RenderPass/DefaultPass.hpp>
#include <OpenGL/Renderer/RenderPass/WireframePass.hpp>
#include <Core/Renderer/Renderer.hpp>
#include <Core/Utility/IndexVector.hpp>

#include <unordered_map>

namespace ax
{
    struct AXION_GL_API RenderContent
    {
        IndexVector<std::pair<MaterialGL, std::vector<Id>>> materials;
        IndexVector<MeshGL> meshes;
        IndexVector<ShaderGL> shaders;
        IndexVector<CameraGL> cameras;
        IndexVector<StaticmeshGL> staticmeshes;
        IndexVector<TextureGL> textures;
        IndexVector<PointLightGL> pointLights;
        IndexVector<DirectionalLightGL> directionalLights;

        Color clearColor = Color(0.0f, 0.0f, 0.0f, 1.0f);
        Vector2u windowSize = Vector2u(0, 0);

        GLuint quadVBO;
        GLuint quadVAO;

        std::unique_ptr<MaterialUBO> materialUBO;
    };

    class AXION_GL_API RendererGL : public Renderer
    {
    public:
        void initialize() noexcept override;
        void terminate() noexcept override;
        void update(double alpha) noexcept override;
        
        //Viewport
        void updateViewport() noexcept override;

        //Rendermode
        void setRenderMode(RenderMode mode) override;
        RenderMode getRenderMode() override;

        //Mesh
        Id createMesh(const std::vector<Vertex>& vertices) override;
        void destroyMesh(Id id) override;
        //Texture
        Id createTexture(
            Vector2u size,
            TextureFormat format,
            const Byte* data
        ) override;
        void destroyTexture(Id id) override;
        //Shader
        Id createShader(
            const std::string* vertex = nullptr,
            const std::string* fragment = nullptr
        ) override;
        void destroyShader(Id id) override;
        //Material
        Id createMaterial(RendererMaterialParameters settings) override;
        void destroyMaterial(Id id) override;

        //Camera
        Id createCamera() override;
        void destroyCamera(Id id) override;
        void setCameraTransform(Id id, Transform* transform) override;
        void setCameraParameters(Id id, RendererCameraParameters settings) override;
        //Staticmesh
        Id createStaticmesh() override;
        void destroyStaticmesh(Id id) override;
        void setStaticmeshMaterial(Id id, Id material) override;
        void setStaticmeshTransform(Id id, Transform* transform) override;
        void setStaticmeshMesh(Id id, Id mesh) override;

        //Light
        Id createPointLight() override;
        void destroyPointLight(Id id) override;
        void setPointLightTransform(Id id, Transform* transform) override;
        void setPointLightParameters(Id id, PointLightParameters parameters) override;

        Id createDirectionalLight() override;
        void destroyDirectionalLight() override;
        void setDirectionalLightParameters(Id id, DirectionalLightParameters parameters) override;

    private:
        void createRenderPass() noexcept;

    private:
        RenderMode m_renderMode = RenderMode::Default;
        std::unique_ptr<RenderPass> m_renderPass;

        RenderContent m_content;
    };
}