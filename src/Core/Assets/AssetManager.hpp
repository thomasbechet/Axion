#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/Utility/Path.hpp>
#include <Core/Utility/Vertex.hpp>
#include <Core/Assets/TextureManager.hpp>
#include <Core/Assets/MeshManager.hpp>
#include <Core/Assets/MaterialManager.hpp>
#include <Core/Assets/ModelManager.hpp>
#include <Core/Assets/PackageManager.hpp>
#include <Core/Assets/ShaderManager.hpp>

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