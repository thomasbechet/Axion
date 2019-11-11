#pragma once

#include <Core/Export.hpp>
#include <Core/Context/Module.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Content/Asset/Mesh.hpp>
#include <Core/Content/Asset/Material.hpp>
#include <Core/Content/Asset/Texture.hpp>
#include <Core/Renderer/RenderMode.hpp>
#include <Core/Renderer/Asset/RendererMaterial.hpp>
#include <Core/Renderer/Asset/RendererMesh.hpp>
#include <Core/Renderer/Asset/RendererShader.hpp>
#include <Core/Renderer/Asset/RendererTexture.hpp>
#include <Core/Renderer/Scene/RendererCamera.hpp>
#include <Core/Renderer/Scene/RendererDirectionalLight.hpp>
#include <Core/Renderer/Scene/RendererPointLight.hpp>
#include <Core/Renderer/Scene/RendererStaticmesh.hpp>
#include <Core/Renderer/GUI/RendererGUIViewport.hpp>
#include <Core/Renderer/GUI/RendererGUILayout.hpp>

#include <string>

namespace ax
{
    class Transform;

    class AXION_CORE_API RendererModule : public Module
    {
    public:
        virtual ~RendererModule() = default;

        virtual void initialize() noexcept = 0;
        virtual void terminate() noexcept = 0;
        virtual void update(double alpha) noexcept = 0;

        //ASSET//////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //Mesh
        virtual RendererMeshHandle createMesh(const std::vector<Vertex>& vertices) = 0;
        virtual void destroyMesh(RendererMeshHandle& mesh) = 0;

        //Texture
        virtual RendererTextureHandle createTexture(Vector2u size, Texture::Format format, const Byte* data) = 0;
        virtual void destroyTexture(RendererTextureHandle& texture) = 0;

        //Shader
        virtual RendererShaderHandle createShader(const std::string* vertex = nullptr, const std::string* fragment = nullptr) = 0;
        virtual void destroyShader(RendererShaderHandle& shader) = 0;

        //Material
        virtual RendererMaterialHandle createMaterial(const RendererMaterialParameters& settings) = 0;
        virtual void destroyMaterial(RendererMaterialHandle& material) = 0;

        //SCENE///////////////////////////////////////////////////////////////////////////////////////////////

        //Camera
        virtual RendererCameraHandle createCamera() = 0;
        virtual void destroyCamera(RendererCameraHandle& camera) = 0;

        //Staticmesh
        virtual RendererStaticmeshHandle createStaticmesh() = 0;
        virtual void destroyStaticmesh(RendererStaticmeshHandle& staticmesh) = 0;

        //PointLight
        virtual RendererPointLightHandle createPointLight() = 0;
        virtual void destroyPointLight(RendererPointLightHandle& pointlight) = 0;

        //DirectionalLight
        virtual RendererDirectionalLightHandle createDirectionalLight() = 0;
        virtual void destroyDirectionalLight(RendererDirectionalLightHandle& directionallight) = 0;

        //GUI////////////////////////////////////////////////////////////////////////////////////////////////

        //Viewport
        virtual RendererGUIViewportHandle createViewport(const Rectf& viewport, const Vector2u& resolution, RenderMode mode = RenderMode::Default) = 0;
        virtual void destroyViewport(RendererGUIViewportHandle& viewport) = 0;

        //Layout
        virtual RendererGUILayoutHandle createGUILayout() = 0;
        virtual void destroyGUILayout(RendererGUILayoutHandle& layout) = 0;
    
        /////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        void setDefaultViewport(RendererGUIViewportHandle viewport) noexcept;
        RendererGUIViewportHandle getDefaultViewport() const noexcept;

    private:
        RendererGUIViewportHandle m_defaultViewport = nullptr; 
    };
}