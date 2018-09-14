#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/Utility/Path.hpp>
#include <Core/Utility/Vertex.hpp>
#include <Core/Assets/Texture.hpp>
#include <Core/Assets/Mesh.hpp>
#include <Core/Assets/Material.hpp>
#include <Core/Assets/Model.hpp>
#include <Core/Assets/Package.hpp>
#include <Core/Assets/Shader.hpp>

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

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