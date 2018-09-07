#pragma once

/////////////
//HEADERS
/////////////
#include <OpenGL/Export.hpp>
#include <OpenGL/Renderer/TextureGL.hpp>
#include <OpenGL/Renderer/MeshGL.hpp>
#include <OpenGL/Renderer/StaticmeshGL.hpp>
#include <OpenGL/Renderer/MaterialGL.hpp>
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
        //Viewport
        void updateViewport() noexcept override;

        //Mesh
        Id createMesh(
            const std::vector<Vector3f>* positions = nullptr,
            const std::vector<Vector2f>* uvs = nullptr,
            const std::vector<Vector3f>* normals = nullptr,
            const std::vector<Vector3f>* tangents = nullptr,
            const std::vector<Vector3f>* bitangents = nullptr
        ) override;
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
        Id createMaterial(MaterialSettings settings) override;
        void destroyMaterial(Id id) override;

        //Camera
        Id createCamera() override;
        void destroyCamera(Id id) override;
        void setCameraTransform(Id id, const Transform& transform) override;
        void setCameraSettings(Id id, CameraSettings settings) override;
        //Staticmesh
        Id createStaticmesh() override;
        void destroyStaticmesh(Id id) override;
        void setStaticmeshMaterial(Id id, Id material) override;
        void setStaticmeshTransform(Id id, const Transform& transform) override;
        void setStaticmeshMesh(Id id, Id mesh) override;

    private:
        std::unordered_map<Id, TextureGL> m_textures;
        std::unordered_map<Id, MeshGL> m_meshes;
        std::unordered_map<Id, StaticmeshGL> m_staticmeshes;
        
        std::unordered_map<Id, std::pair<MaterialGL, std::vector<Id>>> m_materials;        
    };
}