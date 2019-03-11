#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/Asset/AssetReference.hpp>
#include <Core/Asset/Texture.hpp>

namespace ax
{
    class AXION_CORE_API TextureManager
    {
    public:
        AssetReference<Texture> operator()(std::string name) const noexcept;
        AssetReference<Texture> loadFromFile(std::string name, Path path) noexcept;
        AssetReference<Texture> loadFromJson(std::string name, const std::string& json) noexcept;
        bool unload(std::string name) noexcept;
        bool exists(std::string name) const noexcept;

        void dispose() noexcept;
        void log() const noexcept;

    private:
        std::unordered_map<std::string, std::unique_ptr<AssetHolder<Texture>>> m_textures;
    };
}