#pragma once

//////////////
//HEADERS
//////////////
#include <Core/Export.hpp>
#include <Core/Utility/Observer.hpp>

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
        std::vector<Observer<Mesh>> meshes;
        std::vector<Observer<Material>> materials;
        size_t mesh_count;
    };
}