#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Asset/Mesh.hpp>
#include <Core/Asset/Material.hpp>
#include <Core/Asset/Texture.hpp>
#include <Core/Renderer/RenderMode.hpp>
#include <Core/Renderer/Asset/Parameter/RendererMaterialParameters.hpp>
#include <Core/Renderer/Scene/Parameter/RendererCameraParameters.hpp>
#include <Core/Renderer/Scene/Parameter/Light/RendererDirectionalLightParameters.hpp>

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

        //ASSET//////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //Mesh
        virtual RendererMeshPointer createMesh(const std::vector<Vertex>& vertices) = 0;
        virtual void destroyMesh(RendererMesh& mesh) = 0;

        //Texture
        virtual RendererTexturePointer createTexture(Vector2u size, TextureFormat format, const Byte* data) = 0;
        virtual void destroyTexture(RendererTexture& texture) = 0;

        //Shader
        virtual RendererShaderPointer createShader(
            const std::string* vertex = nullptr,
            const std::string* fragment = nullptr
        ) = 0;
        virtual void destroyShader(Id id) = 0;

        virtual RendererShader 

        //Material
        virtual Id createMaterial(const RendererMaterialParameters& settings) = 0;
        virtual void destroyMaterial(Id id) = 0;
        virtual void updateMaterial(Id id, const RendererMaterialParameters& settings) = 0;

        //SCENE///////////////////////////////////////////////////////////////////////////////////////////////

        //Camera
        virtual RendererCameraPointer createCamera() = 0;
        virtual void destroyCamera(RendererCameraPointer& camera) = 0;

        //Staticmesh
        virtual RendererStaticmeshPointer createStaticmesh() = 0;
        virtual void destroyStaticmesh(RendererStaticmeshPointer& staticmesh) = 0;

        //PointLight
        virtual RendererPointLightPointer createPointLight() = 0;
        virtual void destroyPointLight(RendererPointLightPointer& pointlight) = 0;

        //DirectionalLight
        virtual RendererDirectionalLightPointer createDirectionalLight() = 0;
        virtual void destroyDirectionalLight(RendererDirectionalLightPointer& directionallight) = 0;

        //GUI////////////////////////////////////////////////////////////////////////////////////////////////

        //Viewport
        virtual RendererViewport createViewport(const Vector2f& position, const Vector2f& size, RenderMode mode = RenderMode::Default) = 0;
        virtual void destroyViewport(RendererViewport& viewport) = 0;

        //Layout
        virtual RendererGUILayout& createGUILayout() = 0;
        virtual void destroyGUILayout(RendererGUILayout& layout) = 0;

        //GUIButton
        virtual RendererGUIButton& createGUIButton() = 0;
        virtual void destroyGUIButton(RendererGUIButton& button) = 0;
    };
}