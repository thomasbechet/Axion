#pragma once

////////////
//HEADERS
////////////
#include <Core/Export.hpp>
#include <Core/Utility/Color.hpp>
#include <Core/Assets/Texture.hpp>

#include <memory>

namespace ax
{
    struct AXION_CORE_API MaterialParameters
    {
        std::string diffuseTexture = "";
        Color diffuseUniform = Color(1.0f, 1.0f, 1.0f);
        
        std::string normalTexture = "";
    };

    struct AXION_CORE_API Material
    {
        std::string name;

        std::shared_ptr<const Texture> diffuseTexture = nullptr;
        Color diffuseUniform = Color(1.0f, 1.0f, 1.0f, 1.0f);
        
        std::shared_ptr<const Texture> normalTexture = nullptr;

        Id handle;
    };

    class AXION_CORE_API MaterialManager
    {
    public:
        std::shared_ptr<const Material> operator()(std::string name) const noexcept;
        std::shared_ptr<const Material> load(std::string name, const MaterialParameters& params) noexcept;
        bool unload(std::string name, bool tryUnloadTextures = true) noexcept;
        bool isLoaded(std::string name) const noexcept;

        void dispose() noexcept;
        void log() const noexcept;

    private:
        std::unordered_map<std::string, std::shared_ptr<Material>> m_materials;
    };
}