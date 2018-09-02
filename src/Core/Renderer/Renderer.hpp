#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Assets/Mesh.hpp>
#include <Core/Assets/Material.hpp>
#include <Core/Assets/Texture.hpp>
#include <Core/Renderer/CameraSettings.hpp>

#include <string>

namespace ax
{
    class Transform;

    class AXION_CORE_API Renderer
    {
    public:
        friend class GameContext;

    protected:
        virtual void initialize() noexcept = 0;
        virtual void terminate() noexcept = 0;
        virtual void update(double alpha) noexcept = 0;

        //Viewport
        virtual void updateViewport() noexcept = 0;

    public:
        virtual ~Renderer(){}

        //Mesh
        virtual Id loadMesh(
            const std::vector<Vector3f>* positions = nullptr,
            const std::vector<Vector2f>* uvs = nullptr,
            const std::vector<Vector3f>* normals = nullptr,
            const std::vector<Vector3f>* tangents = nullptr,
            const std::vector<Vector3f>* bitangents = nullptr
        ) = 0;
        virtual void unloadMesh(Id id) = 0;
        //Material
        virtual Id loadMaterial(
            
        ) = 0;
        virtual void unloadMaterial(Id id) = 0;
        //Texture
        virtual Id loadTexture(
            Vector2u dimensions,
            TextureFormat format,
            const Byte* data
        ) = 0;
        virtual void unloadTexture(Id id) = 0;
        //Shader
        virtual Id loadShader(
            const std::string* vertex = nullptr
            const std::string* fragment = nullptr
        ) = 0;
        virtual void unloadShader(Id id) = 0;

        //Camera
        virtual Id createCamera() noexcept = 0;
        virtual void destroyCamera(Id id) noexcept = 0;
        virtual void setCameraTransform(Id id, const Transform& transform) noexcept = 0;
        virtual void setCameraSettings(Id id, CameraSettings settings) noexcept = 0;

        //Staticmesh
        virtual Id createStaticmesh() noexcept = 0;
        virtual void destroyStaticmesh(Id id) noexcept = 0;
        virtual void setStaticmeshMaterial(Id id, Id material) noexcept = 0;
        virtual void setStaticmeshTransform(Id id, const Transform& transform) noexcept = 0;
        virtual void setStaticmeshMesh(Id id, Id mesh) noexcept = 0;  
    };
}