#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Asset/Mesh.hpp>
#include <Core/Asset/Material.hpp>
#include <Core/Asset/Texture.hpp>
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
        static constexpr const Id DefaultViewport = 1;

    public:
        virtual ~Renderer() = default;

        virtual void initialize() noexcept = 0;
        virtual void terminate() noexcept = 0;
        virtual void update(double alpha) noexcept = 0;

        //Viewport
        virtual Id createViewport(const Vector2f& position, const Vector2f& size, RenderMode mode = RenderMode::Default) = 0;
        virtual void destroyViewport(Id id) = 0;
        virtual void setViewportRendermode(Id id, RenderMode mode) = 0;
        virtual void setViewportCamera(Id viewport, Id camera) = 0;
        virtual void setViewportResolution(Id viewport, const Vector2u& resolution) = 0;
        virtual void setViewportRectangle(Id viewport, const Vector2f& position, const Vector2f& size) = 0;

        //Mesh
        virtual Id createMesh(const std::vector<Vertex>& vertices) = 0;
        virtual void updateMesh(Id id, const std::vector<Vertex>& vertices) = 0;
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
        virtual Id createMaterial(const RendererMaterialParameters& settings) = 0;
        virtual void destroyMaterial(Id id) = 0;
        virtual void updateMaterial(Id id, const RendererMaterialParameters& settings) = 0;

        //Camera
        virtual Id createCamera() = 0;
        virtual void destroyCamera(Id id) = 0;
        virtual void setCameraTransform(Id id, Transform* transform) = 0;
        virtual void setCameraParameters(Id id, const RendererCameraParameters& settings) = 0;
        //Staticmesh
        virtual Id createStaticmesh() = 0;
        virtual void destroyStaticmesh(Id id) = 0;
        virtual void setStaticmeshMaterial(Id id, Id material) = 0;
        virtual void setStaticmeshTransform(Id id, Transform* transform) = 0;
        virtual void setStaticmeshMesh(Id id, Id mesh) = 0;

        //PointLight
        virtual Id createPointLight() = 0;
        virtual void destroyPointLight(Id id) = 0;
        virtual void setPointLightTransform(Id id, Transform* transform) = 0;
        virtual void setPointLightParameters(Id id, const PointLightParameters& parameters) = 0;
        //DirectionalLight
        virtual Id createPointLight() = 0;
        virtual void destroyPointLight(Id id) = 0;
        virtual void setPointLightParameters(Id id, const DirectionalLightParameters& parameters) = 0;
    };
}