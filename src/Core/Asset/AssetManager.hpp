#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/Utility/Path.hpp>
#include <Core/Math/Geometry/Vertex.hpp>
#include <Core/Asset/TextureManager.hpp>
#include <Core/Asset/MeshManager.hpp>
#include <Core/Asset/MaterialManager.hpp>
#include <Core/Asset/ModelManager.hpp>
#include <Core/Asset/PackageManager.hpp>
#include <Core/Asset/ShaderManager.hpp>

namespace ax
{
    class AXION_CORE_API AssetManager
    {
    public:
        ~AssetManager();

        void dispose() noexcept;
        void log() const noexcept;

        TextureManager texture;
        MeshManager mesh;
        ShaderManager shader;
        MaterialManager material;
        ModelManager model;
        PackageManager package;
    };
}