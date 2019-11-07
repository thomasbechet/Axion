#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Color.hpp>
#include <Core/Utility/Reference.ipp>
#include <Core/Asset/Asset/Texture.hpp>
#include <Core/Asset/Asset/Shader.hpp>
#include <Core/Asset/Asset.hpp>
#include <Core/Renderer/Asset/RendererMaterial.hpp>

namespace ax
{
    class AXION_CORE_API Material : public Asset
    {
    public:
        struct Parameters
        {
            Path source;
            Json json;

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
        static inline const std::string Default = "default_material";

        ASSET_IDENTIFIER("material")

        Material(const std::string& name, const Parameters& parameters);

        Reference<Texture> getDiffuseTexture() const noexcept;
        Color3 getDiffuseColor() const noexcept;
        void setDiffuseColor(Color3 color) noexcept;

        Reference<Texture> getNormalTexture() const noexcept;

        Reference<Texture> getSpecularTexture() const noexcept;
        float getSpecularUniform() const noexcept;
        void setSpecularUniform(float specular) noexcept;

        Reference<Shader> getShader() const noexcept;

        RendererMaterialHandle getHandle() const noexcept;

    private:
        bool onLoad() noexcept override;
        bool onValidate() noexcept override;
        bool onUnload() noexcept override;

    private:
        void update() noexcept;

    private:
        Parameters m_parameters;

        Reference<Texture> m_diffuseTexture;
        Color3 m_diffuseColor = Color3(1.0f, 1.0f, 1.0f);
        
        Reference<Texture> m_normalTexture;
        bool m_isBumpTexture = false;

        Reference<Texture> m_specularTexture;
        float m_specularUniform = 1.0f;

        Reference<Shader> m_shader;

        RendererMaterialHandle m_handle;
    };
}