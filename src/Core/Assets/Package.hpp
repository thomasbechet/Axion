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
#include <Core/Assets/AssetReference.hpp>

#include <string>
#include <memory>
#include <vector>

namespace ax
{
    class AXION_CORE_API Package
    {
    public:
        Package(std::string name);

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

        std::vector<AssetReference<Texture>> m_textures;
        std::vector<AssetReference<Mesh>> m_meshes;
        std::vector<AssetReference<Material>> m_materials;
        std::vector<AssetReference<Model>> m_models;
        std::vector<AssetReference<Shader>> m_shaders;
    };
}