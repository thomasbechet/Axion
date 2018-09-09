#pragma once

/////////////
//HEADERS
/////////////
#include <Core/Export.hpp>
#include <Core/Math/Vector.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Utility/Path.hpp>

#include <unordered_map>
#include <memory>

namespace ax
{
    enum TextureFormat
    {
        RGB,
        RGBA
    };

    struct AXION_CORE_API Texture
    {
        std::string name;

        TextureFormat format;
        Vector2u size;
        Byte* data;

        Id handle;
    };

    class AXION_CORE_API TextureManager
    {
    public:
        std::shared_ptr<const Texture> operator(std::string name) const noexcept;
        std::shared_ptr<const Texture> load(std::string name, Path path) noexcept;
        bool unload(std::string name) noexcept;
        bool isLoaded(std::string name) noexcept;

        void dispose() noexcept;
        void clear() noexcept;

    private:
        std::unordered_map<std::string name, std::shared_ptr<Texture>> m_textures;
    };
}