#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Color.hpp>
#include <Core/Asset/Asset/Texture.hpp>
#include <Core/Asset/Asset/Shader.hpp>
#include <Core/Asset/Asset.hpp>
#include <Core/Asset/AssetReference.hpp>
#include <Core/Asset/AssetHolder.hpp>
#include <Core/Renderer/Asset/RendererMaterial.hpp>

namespace ax
{
    class AXION_CORE_API Material : public Asset
    {
    public:
        struct Parameters
        {
            Path source;
            std::string json;

            bool tryDestroyTextures = true;
            bool tryDestroyShader = true;

            std::string diffuseTexture = "";
            Color3 diffuseColor = Color3(1.0f, 1.0f, 1.0f);
            
            std::string normalTexture = "";
            bool isBumpTexture = false;

            std::string specularTexture = "";
            float specularUniform = 0.5f;

            std::string shader = "";
        };

    public:
        static const std::string Default;
        static const std::string type;

        Material(std::string name, const Parameters& parameters);

        std::string getType() const noexcept override;

        AssetReference<Texture> getDiffuseTexture() const noexcept;
        Color3 getDiffuseColor() const noexcept;
        void setDiffuseColor(Color3 color) noexcept;

        AssetReference<Texture> getNormalTexture() const noexcept;

        AssetReference<Texture> getSpecularTexture() const noexcept;
        float getSpecularUniform() const noexcept;
        void setSpecularUniform(float specular) noexcept;

        AssetReference<Shader> getShader() const noexcept;

        RendererMaterialHandle getHandle() const noexcept;

    private:
        bool onLoad() noexcept override;
        bool onValidate() noexcept override;
        bool onUnload() noexcept override;
        void onError() noexcept override;

    private:
        void update() noexcept;

    private:
        Parameters m_parameters;

        AssetReference<Texture> m_diffuseTexture;
        Color3 m_diffuseColor = Color3(1.0f, 1.0f, 1.0f);
        
        AssetReference<Texture> m_normalTexture;
        bool m_isBumpTexture = false;

        AssetReference<Texture> m_specularTexture;
        float m_specularUniform = 1.0f;

        AssetReference<Shader> m_shader;

        RendererMaterialHandle m_handle;

        std::string m_error;
    };
}