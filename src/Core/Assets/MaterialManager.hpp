#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/Assets/Material.hpp>

namespace ax
{
    class AXION_CORE_API MaterialManager
    {
    public:
        AssetReference<Material> operator()(std::string name) const noexcept;
        AssetReference<Material> create(std::string name, const MaterialParameters& params) noexcept;
        bool destroy(std::string name, bool tryUnloadTextures = true) noexcept;
        bool exists(std::string name) const noexcept;

        void dispose() noexcept;
        void log() const noexcept;

    private:
        std::unordered_map<std::string, std::unique_ptr<AssetHolder<Material>>> m_materials;
    };
}