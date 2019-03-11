#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/Asset/Material.hpp>

namespace ax
{
    class AXION_CORE_API MaterialManager
    {
    public:
        AssetReference<Material> operator()(std::string name) const noexcept;
        AssetReference<Material> loadFromFile(std::string name, Path file) noexcept;
        AssetReference<Material> loadFromJson(std::string name, const std::string& json) noexcept;
        AssetReference<Material> loadFromMemory(std::string name, const MaterialParameters& params) noexcept;
        bool unload(std::string name, bool tryUnloadTextures = true) noexcept;
        bool exists(std::string name) const noexcept;

        void dispose() noexcept;
        void log() const noexcept;

    private:
        std::unordered_map<std::string, std::unique_ptr<AssetHolder<Material>>> m_materials;
    };
}