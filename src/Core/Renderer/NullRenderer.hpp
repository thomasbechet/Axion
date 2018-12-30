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
        Id createViewport(const Vector2f& position, const Vector2f& size, RenderMode rendermode = RenderMode::Default) override {return 0;}
        void destroyViewport(Id id) override {}
        void setViewportRendermode(Id id, RenderMode mode) override {}
        void setViewportCamera(Id viewport, Id camera) override {}
        void setViewportResolution(Id id, const Vector2u& resolution) override {}
        void setViewportRectangle(Id viewport, const Vector2f& position, const Vector2f& size) override {}

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
        Id createMaterial(const RendererMaterialParameters& settings) override {return 0;}
        void destroyMaterial(Id id) override {}
        void updateMaterial(Id id, const RendererMaterialParameters& settings) override {}

        
        //Camera
        Id createCamera() override {return 0;}
        void destroyCamera(Id id) override {}
        void setCameraTransform(Id id, Transform* transform) override {}
        void setCameraParameters(Id id, const RendererCameraParameters& settings) override {}
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
        void setPointLightParameters(Id id, const PointLightParameters& parameters) override {}
    };
}