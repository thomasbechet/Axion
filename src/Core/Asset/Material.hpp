#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Color.hpp>
#include <Core/Asset/Texture.hpp>
#include <Core/Asset/Shader.hpp>
#include <Core/Asset/AssetReference.hpp>
#include <Core/Asset/AssetHolder.hpp>

#include <memory>

namespace ax
{
    struct AXION_CORE_API MaterialParameters
    {
        std::string diffuseTexture = "";
        Color3 diffuseColor = Color3(1.0f, 1.0f, 1.0f);
        
        std::string normalTexture = "";
        bool isBumpTexture = false;

        std::string specularTexture = "";
        float specularUniform = 0.5f;

        std::string shader = "";
    };

    class AXION_CORE_API Material
    {
    public:
        static constexpr const char* Default = "default_material";

        Material();
        Material(std::string name);
        ~Material();

        bool loadFromFile(Path path) noexcept;
        bool loadFromJson(const std::string& json) noexcept;
        bool loadFromMemory(const MaterialParameters& parameters) noexcept;
        bool unload(bool tryDestroyTextures = true, bool tryDestroyShader = true) noexcept;
        bool isLoaded() const noexcept;

        std::string getName() const noexcept;

        AssetReference<Texture> getDiffuseTexture() const noexcept;
        Color3 getDiffuseColor() const noexcept;
        void setDiffuseColor(Color3 color) noexcept;

        AssetReference<Texture> getNormalTexture() const noexcept;

        AssetReference<Texture> getSpecularTexture() const noexcept;
        float getSpecularUniform() const noexcept;
        void setSpecularUniform(float specular) noexcept;

        AssetReference<Shader> getShader() const noexcept;

        Id getHandle() const noexcept;

    private:
        void update() noexcept;

    private:
        std::string m_name;

        bool m_isLoaded = false;

        AssetReference<Texture> m_diffuseTexture;
        Color3 m_diffuseColor = Color3(1.0f, 1.0f, 1.0f);
        
        AssetReference<Texture> m_normalTexture;
        bool m_isBumpTexture = false;

        AssetReference<Texture> m_specularTexture;
        float m_specularUniform = 1.0f;

        AssetReference<Shader> m_shader;

        Id m_handle;
    };
}