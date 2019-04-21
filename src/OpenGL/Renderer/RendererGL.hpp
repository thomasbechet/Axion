#pragma once

#include <OpenGL/Export.hpp>
#include <OpenGL/Renderer/Asset/RendererTextureGL.hpp>
#include <OpenGL/Renderer/Asset/RendererMeshGL.hpp>
#include <OpenGL/Renderer/Asset/RendererMaterialGL.hpp>
#include <OpenGL/Renderer/Asset/RendererShaderGL.hpp>
#include <OpenGL/Renderer/Scene/RendererCameraGL.hpp>
#include <OpenGL/Renderer/Scene/RendererStaticmeshGL.hpp>
#include <OpenGL/Renderer/Scene/RendererPointLightGL.hpp>
#include <OpenGL/Renderer/Scene/RendererDirectionalLightGL.hpp>
#include <OpenGL/Renderer/GUI/RendererGUIViewportGL.hpp>
#include <OpenGL/Renderer/GUI/RendererGUILayoutGL.hpp>
#include <OpenGL/Renderer/Buffer/MaterialUBO.hpp>
#include <OpenGL/Renderer/Buffer/PointLightUBO.hpp>
#include <OpenGL/Renderer/Buffer/DirectionalLightUBO.hpp>
#include <OpenGL/Renderer/Buffer/CameraUBO.hpp>
#include <OpenGL/Renderer/Buffer/ConstantsUBO.hpp>
#include <OpenGL/Renderer/Buffer/CullLightSSBO.hpp>
#include <Core/Renderer/Renderer.hpp>
#include <Core/Utility/IndexVector.hpp>
#include <Core/Asset/Shader.hpp>

namespace ax
{
    struct AXION_GL_API RenderContent
    {
        IndexVector<std::pair<std::unique_ptr<RendererMaterialGL>, std::vector<RendererStaticmeshGL*>>> materials;
        IndexVector<std::unique_ptr<RendererMeshGL>> meshes;
        IndexVector<std::unique_ptr<RendererShaderGL>> shaders;
        IndexVector<std::unique_ptr<RendererTextureGL>> textures;
        
        IndexVector<std::unique_ptr<RendererStaticmeshGL>> staticmeshes;
        IndexVector<std::unique_ptr<RendererPointLightGL>> pointLights;
        IndexVector<std::unique_ptr<RendererDirectionalLightGL>> directionalLights;
        IndexVector<std::unique_ptr<RendererCameraGL>> cameras;

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

        IndexVector<std::unique_ptr<RendererGUIViewportGL>> viewports;
        IndexVector<std::unique_ptr<RendererGUILayoutGL>> layouts;
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
        RendererGUIViewportHandle createViewport(const Vector2f& position, const Vector2f& size, RenderMode mode = RenderMode::Default) override;
        void destroyViewport(RendererGUIViewportHandle& viewport) override;

        //Layout
        RendererGUILayoutHandle createGUILayout() override;
        void destroyGUILayout(RendererGUILayoutHandle& layout) override;

    private:
        RenderContent m_content;
    };
}