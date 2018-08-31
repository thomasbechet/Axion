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
}