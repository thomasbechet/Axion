#pragma once

/////////////
//HEADERS
/////////////
#include <Core/Export.hpp>
#include <Core/Math/Vector.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Utility/Path.hpp>

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

namespace ax
{
    struct AXION_CORE_API Mesh
    {
        std::vector<Vector3f> positions;
        std::vector<Vector2f> uvs;
        std::vector<Vector3f> normals;
        std::vector<Vector3f> tangents;
        std::vector<Vector3f> bitangents;
        std::vector<Vector3f> colors;
        size_t vertex_count;
        Id id;
    };
}