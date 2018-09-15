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
        void setCameraTransform(Id id, const Transform& transform) override {}
        void setCameraSettings(Id id, RendererCameraParameters settings) override {}
        //Staticmesh
        Id createStaticmesh() override {return 0;}
        void destroyStaticmesh(Id id) override {}
        void setStaticmeshMaterial(Id id, Id material) override {}
        void setStaticmeshTransform(Id id, const Transform& transform) override {}
        void setStaticmeshMesh(Id id, Id mesh) override {}
    };
}