#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/Renderer/Renderer.hpp>

namespace ax
{
    class AXION_CORE_API NullRenderer : public Renderer
    {
    protected:
        void initialize() noexcept override {}
        void terminate() noexcept override {}
        void update(double alpha) noexcept override {}

    public:
        //Mesh
        virtual Id loadMesh(const Mesh& mesh) noexcept override {return 0;}
        virtual void unloadMesh(Id mesh) noexcept override {}
        //Material
        virtual Id loadMaterial(const Material& material) noexcept override {return 0;}
        virtual void unloadMaterial(Id material) noexcept override {}
        //Texture
        virtual Id loadTexture(const Texture& texture) noexcept override {return 0;}
        virtual void unloadTexture(Id material) noexcept override {}
        //Shader
        virtual Id loadShader(const std::string& vertex, const std::string& fragment) noexcept override {return 0;}
        virtual void unloadShader(Id shader) noexcept override {}

        //Camera
        virtual Id createCamera() noexcept override {}
        virtual void destroyCamera(Id id) noexcept override {}
        virtual void setCameraTransform(Id id, const Transform& transform) noexcept override {}
        virtual void setCameraSettings(Id id, CameraSettings settings) noexcept override {}

        //Staticmesh
        virtual Id createStaticmesh() noexcept override {}
        virtual void destroyStaticmesh(Id id) noexcept override {}
        virtual void setStaticmeshMaterial(Id id, std::string name) noexcept override {}
        virtual void setStaticmeshTransform(Id id, const Transform& transform) noexcept override {}
        virtual void setStaticmeshMesh(Id id, std::string name) noexcept override {}
    
        //Window resize
        virtual void updateViewport() noexcept override {}
    };
}