#pragma once

/////////////
//HEADERS
/////////////
#include <Core/Export.hpp>
#include <Core/Assets/Texture.hpp>
#include <Core/Assets/Mesh.hpp>
#include <Core/Assets/Material.hpp>
#include <Core/Assets/Model.hpp>
#include <Core/Assets/Shader.hpp>

#include <string>
#include <memory>
#include <vector>

namespace ax
{
    struct AXION_CORE_API Package
    {
        std::string name;

        std::vector<AssetReference<Texture>> textures;
        std::vector<AssetReference<Mesh>> meshes;
        std::vector<AssetReference<Material>> materials;
        std::vector<AssetReference<Model>> models;
        std::vector<AssetReference<Shader>> shaders;
    };

    class AXION_CORE_API PackageManager
    {
    public:
        AssetReference<Package> operator()(std::string name) const noexcept;
        AssetReference<Package> load(Path path) noexcept;
        bool unload(std::string name) noexcept;
        bool isLoaded(std::string name) const noexcept;

        void dispose() noexcept;
        void log() const noexcept;

    private:
        std::unordered_map<std::string, std::unique_ptr<AssetReference<Package>>> m_packages;
    };
}