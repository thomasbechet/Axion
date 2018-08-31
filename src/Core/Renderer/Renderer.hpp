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

    public:
        virtual ~Renderer(){}

        //Mesh
        virtual Id loadMesh(const Mesh& mesh) noexcept = 0;
        virtual void unloadMesh(Id mesh) noexcept = 0;
        //Material
        virtual Id loadMaterial(const Material& material) noexcept = 0;
        virtual void unloadMaterial(Id material) noexcept = 0;
        //Texture
        virtual Id loadTexture(const Texture& texture) noexcept = 0;
        virtual void unloadTexture(Id material) noexcept = 0;
        //Shader
        virtual Id loadShader(const std::string& vertex, const std::string& fragment) noexcept = 0;
        virtual void unloadShader(Id shader) noexcept = 0;

        //Camera
        virtual Id createCamera() noexcept = 0;
        virtual void destroyCamera(Id id) noexcept = 0;
        virtual void setCameraTransform(Id id, const Transform& transform) noexcept = 0;
        virtual void setCameraSettings(Id id, CameraSettings settings) noexcept = 0;

        //Staticmesh
        virtual Id createStaticmesh() noexcept = 0;
        virtual void destroyStaticmesh(Id id) noexcept = 0;
        virtual void setStaticmeshMaterial(Id id, std::string name) noexcept = 0;
        virtual void setStaticmeshTransform(Id id, const Transform& transform) noexcept = 0;
        virtual void setStaticmeshMesh(Id id, std::string name) noexcept = 0;
    
        //Viewport
        virtual void updateViewport() noexcept = 0;
    };
}