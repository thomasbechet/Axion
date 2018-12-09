#pragma once

////////////
//HEADERS
////////////
#include <Core/Export.hpp>
#include <Core/Utility/Color.hpp>
#include <Core/Assets/Texture.hpp>
#include <Core/Assets/AssetReference.hpp>
#include <Core/Assets/AssetHolder.hpp>

#include <memory>

namespace ax
{
    struct AXION_CORE_API MaterialParameters
    {
        std::string diffuseTexture = "";
        Color diffuseColor = Color(1.0f, 1.0f, 1.0f);
        
        std::string normalTexture = "";
        bool isBumpTexture;
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
        Color getDiffuseColor() const noexcept;
        AssetReference<Texture> getNormalTexture() const noexcept;

        Id getHandle() const noexcept;

    private:
        std::string m_name;

        bool m_isLoaded = false;

        AssetReference<Texture> m_diffuseTexture;
        Color m_diffuseColor = Color(1.0f, 1.0f, 1.0f, 1.0f);
        
        AssetReference<Texture> m_normalTexture;

        Id m_handle;
    };
}