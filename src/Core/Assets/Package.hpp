#pragma once

/////////////
//HEADERS
/////////////
#include <Core/Export.hpp>

#include <string>
#include <vector>

namespace ax
{
    struct AXION_CORE_API Package
    {
        std::vector<std::string> textures;
        std::vector<std::string> meshes;
        std::vector<std::string> materials;
        std::vector<std::string> models;
    };
}