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
#include <Core/Renderer/Renderer.hpp>
#include <Core/Utility/IndexVector.hpp>

#include <unordered_map>

namespace ax
{
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
        void initializeRenderPass() noexcept;
        void renderRenderPass(double alpha) noexcept;
        void terminateRenderPass() noexcept;

    private:
        void initializeDefault() noexcept;
        void renderDefault(double alpha) noexcept;
        void terminateDefault() noexcept;

        void initializeWireframe() noexcept;
        void renderWireframe(double alpha) noexcept;
        void terminateWireframe() noexcept;

        void initializeDebug() noexcept;
        void renderDebug(double alpha, int mode) noexcept;
        void terminateDebug() noexcept;

    private:
        IndexVector<std::pair<MaterialGL, std::vector<Id>>> m_materials;
        IndexVector<MeshGL> m_meshes;
        IndexVector<ShaderGL> m_shaders;
        IndexVector<CameraGL> m_cameras;
        IndexVector<StaticmeshGL> m_staticmeshes;
        IndexVector<TextureGL> m_textures;
        IndexVector<PointLightGL> m_pointLights;
        IndexVector<DirectionalLightGL> m_directionalLights;

        RenderMode m_renderMode = RenderMode::Default;
        Color m_clearColor = Color(0.0f, 0.0f, 0.0f, 1.0f);

        AssetReference<Shader> m_defaultShader;
        AssetReference<Shader> m_wireframeShader;
        AssetReference<Shader> m_debugShader;
    };
}