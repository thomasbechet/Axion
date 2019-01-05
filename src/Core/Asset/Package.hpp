#pragma once

/////////////
//HEADERS
/////////////
#include <Core/Export.hpp>
#include <Core/Asset/Texture.hpp>
#include <Core/Asset/Mesh.hpp>
#include <Core/Asset/Material.hpp>
#include <Core/Asset/Model.hpp>
#include <Core/Asset/Shader.hpp>
#include <Core/Asset/AssetReference.hpp>

#include <string>
#include <memory>
#include <vector>

namespace ax
{
    class AXION_CORE_API Package
    {
    public:
        Package();
        Package(std::string name);
        ~Package();

        bool loadFromFile(Path path) noexcept;
        bool unload() noexcept;

        std::string getName() const noexcept;

        const std::vector<AssetReference<Texture>>& getTextures() const noexcept;
        const std::vector<AssetReference<Mesh>>& getMeshes() const noexcept;
        const std::vector<AssetReference<Material>>& getMaterials() const noexcept;
        const std::vector<AssetReference<Model>>& getModels() const noexcept;
        const std::vector<AssetReference<Shader>>& getShaders() const noexcept;

    private:
        std::string m_name;

        bool m_isLoaded = false;

        std::vector<AssetReference<Texture>> m_textures;
        std::vector<AssetReference<Mesh>> m_meshes;
        std::vector<AssetReference<Material>> m_materials;
        std::vector<AssetReference<Model>> m_models;
        std::vector<AssetReference<Shader>> m_shaders;
    };
}