#pragma once

//////////////
//HEADERS
//////////////
#include <Core/Export.hpp>
#include <Core/Asset/Mesh.hpp>
#include <Core/Asset/Material.hpp>
#include <Core/Utility/Path.hpp>

#include <unordered_map>
#include <memory>
#include <string>
#include <vector>

namespace ax
{
    class AXION_CORE_API Model
    {
    public:
        Model();
        Model(std::string name);
        ~Model();

        bool loadFromFile(Path path) noexcept;
        bool unload(bool tryDestroyMeshes = true, bool tryDestroyMaterials = true, bool tryDestroyTextures = true) noexcept;
        bool isLoaded() const noexcept;

        std::string getName() const noexcept;

        const std::vector<AssetReference<Mesh>>& getMeshes() const noexcept;
        const std::vector<AssetReference<Material>>& getMaterials() const noexcept;

    private:
        bool loadObjModel(Path path) noexcept;

    private:
        std::string m_name;

        bool m_isLoaded = false;

        std::vector<AssetReference<Mesh>> m_meshes;
        std::vector<AssetReference<Material>> m_materials;
    };
}