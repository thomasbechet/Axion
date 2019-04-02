#pragma once

#include <OpenGL/Export.hpp>
#include <OpenGL/Renderer/Asset/TextureGL.hpp>
#include <OpenGL/Renderer/Asset/MeshGL.hpp>
#include <OpenGL/Renderer/Asset/MaterialGL.hpp>
#include <OpenGL/Renderer/Asset/ShaderGL.hpp>
#include <OpenGL/Renderer/Scene/CameraGL.hpp>
#include <OpenGL/Renderer/Scene/RendererStaticmeshGL.hpp>
#include <OpenGL/Renderer/Scene/Light/PointLightGL.hpp>
#include <OpenGL/Renderer/Scene/Light/DirectionalLightGL.hpp>
#include <OpenGL/Renderer/Buffer/MaterialUBO.hpp>
#include <OpenGL/Renderer/Buffer/PointLightUBO.hpp>
#include <OpenGL/Renderer/Buffer/DirectionalLightUBO.hpp>
#include <OpenGL/Renderer/Buffer/CameraUBO.hpp>
#include <OpenGL/Renderer/Buffer/ConstantsUBO.hpp>
#include <OpenGL/Renderer/Buffer/CullLightSSBO.hpp>
#include <OpenGL/Renderer/RenderPass/RenderPass.hpp>
#include <Core/Renderer/Renderer.hpp>
#include <Core/Utility/IndexVector.hpp>
#include <Core/Asset/Shader.hpp>

#include <unordered_map>

namespace ax
{
    struct AXION_GL_API RenderContent
    {
        IndexVector<std::pair<std::unique_ptr<MaterialGL>, std::vector<RendererStaticmeshGL*>>> materials;
        IndexVector<unique_ptr<RendererMeshGL>> meshes;
        IndexVector<unique_ptr<RendererShaderGL>> shaders;
        IndexVector<unique_ptr<RendererTextureGL>> textures;
        
        IndexVector<unique_ptr<RendererStaticmeshGL>> staticmeshes;
        IndexVector<unique_ptr<RendererPointLightGL>> pointLights;
        IndexVector<unique_ptr<RendererDirectionalLightGL>> directionalLights;
        IndexVector<unique_ptr<RendererCameraGL>> cameras;

        GLuint quadVBO;
        GLuint quadVAO;

        AssetReference<Shader> debugLightCullingShader;
        AssetReference<Shader> geometryShader;
        AssetReference<Shader> genericShader;
        AssetReference<Shader> postProcessShader;
        AssetReference<Shader> quadTextureShader;
        AssetReference<Shader> wireframeShader;
        ShaderGLSL lightCullingComputeShader;

        std::unique_ptr<MaterialUBO> materialUBO;
        std::unique_ptr<PointLightUBO> pointLightUBO;
        std::unique_ptr<DirectionalLightUBO> directionalLightUBO;
        std::unique_ptr<CameraUBO> cameraUBO;
        std::unique_ptr<ConstantsUBO> constantsUBO;
        std::unique_ptr<CullLightSSBO> cullLightSSBO;
    };

    struct AXION_GL_API Viewport
    {
        Color3 clearColor = Color3(0.0f, 0.0f, 0.0f);

        Vector2u resolution = Vector2u(0, 0);
        Vector2f position = Vector2f(0.0f, 0.0f);
        Vector2f size = Vector2f(1.0f, 1.0f);

        std::unique_ptr<RenderPass> renderPass;
        Id camera = 0;
    };

    class AXION_GL_API RendererGL : public Renderer
    {
    public:
        void initialize() noexcept override;
        void terminate() noexcept override;
        void update(double alpha) noexcept override;

        //ASSET//////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //Mesh
        RendererMeshHandle createMesh(const std::vector<Vertex>& vertices) override;
        void destroyMesh(RendererMeshHandle& mesh) override;

        //Texture
        RendererTextureHandle createTexture(Vector2u size, TextureFormat format, const Byte* data) override;
        void destroyTexture(RendererTextureHandle& texture) override;

        //Shader
        RendererShaderHandle createShader(const std::string* vertex = nullptr, const std::string* fragment = nullptr) override;
        void destroyShader(RendererShaderHandle& shader) override;

        //Material
        RendererMaterialHandle createMaterial(const RendererMaterialParameters& settings) override;
        void destroyMaterial(RendererMaterialHandle& material) override;

        //SCENE///////////////////////////////////////////////////////////////////////////////////////////////

        //Camera
        RendererCameraHandle createCamera() override;
        void destroyCamera(RendererCameraHandle& camera) override;

        //Staticmesh
        RendererStaticmeshHandle createStaticmesh() override;
        void destroyStaticmesh(RendererStaticmeshHandle& staticmesh) override;

        //PointLight
        RendererPointLightHandle createPointLight() override;
        void destroyPointLight(RendererPointLightHandle& pointlight) override;

        //DirectionalLight
        RendererDirectionalLightHandle createDirectionalLight() override;
        void destroyDirectionalLight(RendererDirectionalLightHandle& directionallight) override;

        //GUI////////////////////////////////////////////////////////////////////////////////////////////////

        //Viewport
        RendererViewportHandle createViewport(const Vector2f& position, const Vector2f& size, RenderMode mode = RenderMode::Default) override;
        void destroyViewport(RendererViewport& viewport) override;

        //Layout
        //virtual RendererGUILayout& createGUILayout() = 0;
        //virtual void destroyGUILayout(RendererGUILayout& layout) = 0;

        //GUIButton
        //virtual RendererGUIButton& createGUIButton() = 0;
        //virtual void destroyGUIButton(RendererGUIButton& button) = 0;

    private:
        RenderContent m_content;
        IndexVector<std::unique_ptr<Viewport>> m_viewports;
    };
}