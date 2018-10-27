#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/Renderer/Renderer.hpp>
#include <Core/Renderer/RendererException.hpp>

namespace ax
{
    class AXION_CORE_API NullRenderer : public Renderer
    {
    protected:
        void initialize() noexcept override {}
        void terminate() noexcept override {}
        void update(double alpha) noexcept override {}

    public:
        //Viewport
        void updateViewport() noexcept override {}

        //Rendermode
        void setRenderMode(RenderMode mode) override {};
        RenderMode getRenderMode() override {return RenderMode::Default;};

        //Mesh
        Id createMesh(const std::vector<Vertex>& vertices) override {return 0;}
        void destroyMesh(Id id) override {}
        //Texture
        Id createTexture(
            Vector2u size,
            TextureFormat format,
            const Byte* data
        ) override {return 0;}
        void destroyTexture(Id id) override {}
        //Shader
        Id createShader(
            const std::string* vertex = nullptr,
            const std::string* fragment = nullptr
        ) override {return 0;}
        void destroyShader(Id id) override {}
        //Material
        Id createMaterial(RendererMaterialParameters settings) override {return 0;}
        void destroyMaterial(Id id) override {}
        
        //Camera
        Id createCamera() override {return 0;}
        void destroyCamera(Id id) override {}
        void setCameraTransform(Id id, Transform* transform) override {}
        void setCameraParameters(Id id, RendererCameraParameters settings) override {}
        //Staticmesh
        Id createStaticmesh() override {return 0;}
        void destroyStaticmesh(Id id) override {}
        void setStaticmeshMaterial(Id id, Id material) override {}
        void setStaticmeshTransform(Id id, Transform* transform) override {}
        void setStaticmeshMesh(Id id, Id mesh) override {}

        //Light
        Id createPointLight() override {return 0;}
        void destroyPointLight(Id id) override {}
        void setPointLightTransform(Id id, Transform* transform) override {}
        void setPointLightParameters(Id id, PointLightParameters parameters) override {}

        Id createDirectionalLight() override {return 0;}
        void destroyDirectionalLight() override {}
        void setDirectionalLightParameters(Id id, DirectionalLightParameters parameters) override {}
    };
}