#pragma once

/////////////
//HEADERS
/////////////
#include <OpenGL/Export.hpp>
#include <Core/Renderer/Renderer.hpp>

#include <unordered_map>

namespace ax
{
    class AXION_GL_API RendererGL : public Renderer
    {
    protected:
        void initialize() noexcept override;
        void terminate() noexcept override;
        void update(double alpha) noexcept override;

    public:
        //Mesh
        Id loadMesh(const Mesh& mesh) noexcept override;
        void unloadMesh(Id mesh) noexcept override;
        //Material
        Id loadMaterial(const Material& material) noexcept override;
        void unloadMaterial(Id material) noexcept override;
        //Texture
        Id loadTexture(const Texture& texture) noexcept override;
        void unloadTexture(Id material) noexcept override;

        //Camera
        Id createCamera() noexcept override;
        void destroyCamera(Id id) noexcept override;
        void setCameraTransform(Id id, const Transform& transform) noexcept override;
        void setCameraSettings(Id id, CameraSettings settings) noexcept override;

        //Staticmesh
        Id createStaticmesh() noexcept override;
        void destroyStaticmesh(Id id) noexcept override;
        void setStaticmeshMaterial(Id id, std::string name) noexcept override;
        void setStaticmeshTransform(Id id, const Transform& trans) noexcept override;
        void setStaticmeshMesh(Id id, std::string name) noexcept override;
    
        void updateViewport() noexcept override;

    private:
        std::unordered_map<Id, TextureGL> m_textures;
        std::unordered_map<Id, MeshGL> m_meshes;

        std::unordered_map<Id, StaticmeshGL> m_staticmeshes;
        
    };
}