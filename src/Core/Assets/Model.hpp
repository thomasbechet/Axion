#pragma once

//////////////
//HEADERS
//////////////
#include <Core/Export.hpp>

#include <unordered_map>
#include <memory>
#include <string>

namespace ax
{
    struct AXION_CORE_API Model
    {
        std::string name;

        std::vector<std::shared_ptr<const Mesh>> meshes;
        std::vector<std::shared_ptr<const Material>> materials;
    };
}