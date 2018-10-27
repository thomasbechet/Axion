#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Assets/Mesh.hpp>
#include <Core/Assets/Material.hpp>
#include <Core/Assets/Texture.hpp>
#include <Core/Renderer/RenderMode.hpp>
#include <Core/Renderer/RendererCameraParameters.hpp>
#include <Core/Renderer/RendererMaterialParameters.hpp>
#include <Core/Renderer/Light/PointLightParameters.hpp>
#include <Core/Renderer/Light/DirectionalLightParameters.hpp>

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

        //Rendermode
        virtual void setRenderMode(RenderMode mode) = 0;
        virtual RenderMode getRenderMode() = 0;

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
        virtual void setCameraTransform(Id id, Transform* transform) = 0;
        virtual void setCameraParameters(Id id, RendererCameraParameters settings) = 0;
        //Staticmesh
        virtual Id createStaticmesh() = 0;
        virtual void destroyStaticmesh(Id id) = 0;
        virtual void setStaticmeshMaterial(Id id, Id material) = 0;
        virtual void setStaticmeshTransform(Id id, Transform* transform) = 0;
        virtual void setStaticmeshMesh(Id id, Id mesh) = 0;

        //Light
        virtual Id createPointLight() = 0;
        virtual void destroyPointLight(Id id) = 0;
        virtual void setPointLightTransform(Id id, Transform* transform) = 0;
        virtual void setPointLightParameters(Id id, PointLightParameters parameters) = 0;

        virtual Id createDirectionalLight() = 0;
        virtual void destroyDirectionalLight() = 0;
        virtual void setDirectionalLightParameters(Id id, DirectionalLightParameters parameters) = 0;
    };
}