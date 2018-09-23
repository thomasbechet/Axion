#pragma once

//////////////
//HEADERS
//////////////
#include <Core/Export.hpp>
#include <Core/Assets/Mesh.hpp>
#include <Core/Assets/Material.hpp>
#include <Core/Utility/Path.hpp>

#include <unordered_map>
#include <memory>
#include <string>
#include <vector>

namespace ax
{
    struct AXION_CORE_API Model
    {
        std::string name;

        std::vector<AssetReference<Mesh>> meshes;
        std::vector<AssetReference<Material>> materials;
    };

    class AXION_CORE_API ModelManager
    {
    public:
        AssetReference<Model> operator()(std::string name) const noexcept;
        AssetReference<Model> load(std::string name, Path path) noexcept;
        bool unload(std::string name, bool tryUnloadMeshes = true, bool tryUnloadMaterials = true, bool tryUnloadTextures = true) noexcept;
        bool isLoaded(std::string name) const noexcept;

        void dispose() noexcept;
        void log() const noexcept;

    private:
        AssetReference<Model> loadObjModel(std::string name, Path path) noexcept;

        std::unordered_map<std::string, std::unique_ptr<AssetHolder<Model>>> m_models;
    };
}