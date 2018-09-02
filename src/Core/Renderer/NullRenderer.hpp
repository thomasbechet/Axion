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

        //Viewport
        void updateViewport() noexcept override {}

    public:
        //Mesh
        bool loadMesh(Mesh& mesh) noexcept override {return true;}
        bool unloadMesh(Mesh& mesh) noexcept override {return true;}
        //Material
        bool loadMaterial(Material& material) noexcept override {return true;}
        bool unloadMaterial(Material& material) noexcept override {return true;}
        //Texture
        bool loadTexture(Texture& texture) noexcept override {return true;}
        bool unloadTexture(Texture& texture) noexcept override {return true;}
        //Shader
        bool loadShader(Shader& shader) noexcept override {return true;}
        bool unloadShader(Shader& shader) noexcept override {return true;}

        //Camera
        Id createCamera() noexcept override {return 0;}
        void destroyCamera(Id id) noexcept override {}
        void setCameraTransform(Id id, const Transform& transform) noexcept override {}
        void setCameraSettings(Id id, CameraSettings settings) noexcept override {}

        //Staticmesh
        Id createStaticmesh() noexcept override {}
        void destroyStaticmesh(Id id) noexcept override {}
        void setStaticmeshMaterial(Id id, std::string name) noexcept override {}
        void setStaticmeshTransform(Id id, const Transform& transform) noexcept override {}
        void setStaticmeshMesh(Id id, std::string name) noexcept override {}
    };
}