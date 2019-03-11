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
        RGBA,
        R,
        G,
        B
    };

    class AXION_CORE_API Texture
    {
    public:
        Texture();
        Texture(std::string name);
        ~Texture();

        bool loadFromFile(Path path) noexcept;
        bool loadFromJson(const std::string& json) noexcept;
        bool unload() noexcept;
        bool isLoaded() const noexcept;

        std::string getName() const noexcept;
        Vector2u getSize() const noexcept;
        TextureFormat getFormat() const noexcept;

        Id getHandle() const noexcept;

    private:
        std::string m_name;

        bool m_isLoaded = false;

        TextureFormat m_format = TextureFormat::RGB;
        Vector2u m_size = Vector2u(0, 0);
        Byte* m_data = nullptr;

        Id m_handle;
    };
}