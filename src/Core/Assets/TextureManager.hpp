#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/Assets/AssetReference.hpp>
#include <Core/Assets/Texture.hpp>

namespace ax
{
    class AXION_CORE_API TextureManager
    {
    public:
        AssetReference<Texture> operator()(std::string name) const noexcept;
        AssetReference<Texture> create(std::string name, Path path) noexcept;
        bool destroy(std::string name) noexcept;
        bool exists(std::string name) const noexcept;

        void dispose() noexcept;
        void log() const noexcept;

    private:
        std::unordered_map<std::string, std::unique_ptr<AssetHolder<Texture>>> m_textures;
    };
}