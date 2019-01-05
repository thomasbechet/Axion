#pragma once

////////////
//HEADERS
////////////
#include <Core/Export.hpp>
#include <Core/Utility/Color.hpp>
#include <Core/Asset/Texture.hpp>
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
    };

    class AXION_CORE_API Material
    {
    public:
        static constexpr const char* Default = "default_material";

        Material();
        Material(std::string name);
        ~Material();

        bool load(const MaterialParameters& parameters) noexcept;
        bool unload(bool tryDestroyTextures = true) noexcept;
        bool isLoaded() const noexcept;

        std::string getName() const noexcept;

        AssetReference<Texture> getDiffuseTexture() const noexcept;
        Color3 getDiffuseColor() const noexcept;
        void setDiffuseColor(Color3 color) noexcept;
        AssetReference<Texture> getNormalTexture() const noexcept;

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

        Id m_handle;
    };
}