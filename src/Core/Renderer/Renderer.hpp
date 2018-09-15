#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Assets/Mesh.hpp>
#include <Core/Assets/Material.hpp>
#include <Core/Assets/Texture.hpp>
#include <Core/Renderer/RendererCameraParameters.hpp>
#include <Core/Renderer/RendererMaterialParameters.hpp>

#include <string>

namespace ax
{
    class Transform;

    class AXION_CORE_API Renderer
    {
    public:
        virtual ~Renderer(){}

        virtual void initialize() noexcept = 0;
        virtual void terminate() noexcept = 0;
        virtual void update(double alpha) noexcept = 0;

        //Viewport
        virtual void updateViewport() noexcept = 0;

        //Mesh
        virtual Id createMesh(const std::vector<Vertex>& vertices) = 0;
        virtual void destroyMesh(Id id) = 0;
        //Texture
        virtual Id createTexture(
            Vector2u size,
            TextureFormat format,
            const Byte* data
        ) = 0;
        virtual void destroyTexture(Id id) = 0;
        //Shader
        virtual Id createShader(
            const std::string* vertex = nullptr,
            const std::string* fragment = nullptr
        ) = 0;
        virtual void destroyShader(Id id) = 0;
        //Material
        virtual Id createMaterial(RendererMaterialParameters settings) = 0;
        virtual void destroyMaterial(Id id) = 0;

        //Camera
        virtual Id createCamera() = 0;
        virtual void destroyCamera(Id id) = 0;
        virtual void setCameraTransform(Id id, const Transform& transform) = 0;
        virtual void setCameraSettings(Id id, RendererCameraParameters settings) = 0;
        //Staticmesh
        virtual Id createStaticmesh() = 0;
        virtual void destroyStaticmesh(Id id) = 0;
        virtual void setStaticmeshMaterial(Id id, Id material) = 0;
        virtual void setStaticmeshTransform(Id id, const Transform& transform) = 0;
        virtual void setStaticmeshMesh(Id id, Id mesh) = 0;
    };
}