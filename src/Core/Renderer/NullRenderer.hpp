#pragma once

#include <Core/Export.hpp>
#include <Core/Renderer/Renderer.hpp>
#include <Core/Renderer/RendererException.hpp>

namespace ax
{
    class AXION_CORE_API NullRenderer : public Renderer
    {
    public:
        void initialize() noexcept override {}
        void terminate() noexcept override {}
        void update(double alpha) noexcept override {}

        //ASSET//////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //Mesh
        RendererMeshHandle createMesh(const std::vector<Vertex>& vertices) override {return &m_nullMesh;}
        void destroyMesh(RendererMeshHandle& mesh) override {}

        //Texture
        RendererTextureHandle createTexture(Vector2u size, TextureFormat format, const Byte* data) override {return &m_nullTexture;}
        void destroyTexture(RendererTextureHandle& texture) override {}

        //Shader
        RendererShaderHandle createShader(const std::string* vertex = nullptr, const std::string* fragment = nullptr) override {return &m_nullShader;}
        void destroyShader(RendererShaderHandle& shader) override {}

        //Material
        RendererMaterialHandle createMaterial(const RendererMaterialParameters& settings) override {return &m_nullMaterial;}
        void destroyMaterial(RendererMaterialHandle& material) override {}

        //SCENE///////////////////////////////////////////////////////////////////////////////////////////////

        //Camera
        RendererCameraHandle createCamera() override {return &m_nullCamera;}
        void destroyCamera(RendererCameraHandle& camera) override {}

        //Staticmesh
        RendererStaticmeshHandle createStaticmesh() override {return &m_nullStaticmesh;}
        void destroyStaticmesh(RendererStaticmeshHandle& staticmesh) override {}

        //PointLight
        RendererPointLightHandle createPointLight() override {return &m_nullPointLight;}
        void destroyPointLight(RendererPointLightHandle& pointlight) override {}

        //DirectionalLight
        RendererDirectionalLightHandle createDirectionalLight() override {return &m_nullDirectionalLight;}
        void destroyDirectionalLight(RendererDirectionalLightHandle& directionallight) override {}

        //GUI////////////////////////////////////////////////////////////////////////////////////////////////

        //Viewport
        RendererViewportHandle createViewport(const Vector2f& position, const Vector2f& size, RenderMode mode = RenderMode::Default) override {return &m_nullViewport;}
        void destroyViewport(RendererViewportHandle& viewport) override {}

    private:
        NullRendererMesh m_nullMesh;
        NullRendererTexture m_nullTexture;
        NullRendererShader m_nullShader;
        NullRendererMaterial m_nullMaterial;

        NullRendererViewport m_nullViewport;

        NullRendererCamera m_nullCamera;
        NullRendererStaticMesh m_nullStaticmesh;
        NullRendererPointLight m_nullPointLight;
        NullRendererDirectionalLight m_nullDirectionalLight;
    };
}