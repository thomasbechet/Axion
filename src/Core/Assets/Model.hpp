#pragma once

//////////////
//HEADERS
//////////////
#include <Core/Export.hpp>

#include <vector>
#include <unordered_map>
#include <memory>

namespace ax
{
    struct AXION_CORE_API ModelData
    {

    };

    struct AXION_CORE_API Model
    {
        std::vector<std::shared_ptr<const Mesh>> meshes;
        std::vector<std::shared_ptr<const Material>> materials;
        size_t mesh_count;
    };
}