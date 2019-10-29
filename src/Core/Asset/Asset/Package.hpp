#pragma once

#include <Core/Export.hpp>
#include <Core/Asset/Asset/Material.hpp>
#include <Core/Asset/Asset/Mesh.hpp>
#include <Core/Asset/Asset/Model.hpp>
#include <Core/Asset/Asset/Scene.hpp>
#include <Core/Asset/Asset/Shader.hpp>
#include <Core/Asset/Asset/Texture.hpp>
#include <Core/Asset/AssetReference.hpp>
#include <Core/Asset/Asset.hpp>

#include <string>
#include <memory>
#include <vector>

namespace ax
{
    class AXION_CORE_API Package : public Asset
    {
    public:
        struct Parameters
        {
            Path source;
            Json json;
            bool asyncLoading = false;
        };

    public:
        ASSET_IDENTIFIER("package")
        
        Package(const std::string& name, const Parameters& parameters);

        const std::vector<AssetReference<Material>>& getMaterials() const noexcept;
        const std::vector<AssetReference<Mesh>>& getMeshes() const noexcept;
        const std::vector<AssetReference<Model>>& getModels() const noexcept;
        const std::vector<AssetReference<Scene>>& getScenes() const noexcept;
        const std::vector<AssetReference<Shader>>& getShaders() const noexcept;
        const std::vector<AssetReference<Texture>>& getTextures() const noexcept;

    private:
        bool onLoad() noexcept override;
        bool onValidate() noexcept override;
        bool onUnload() noexcept override;
        void onError() noexcept override;

    private:
        bool loadFromJson(Json& json) noexcept;

    private:
        Parameters m_parameters;

        std::vector<AssetReference<Material>> m_materials;
        std::vector<AssetReference<Mesh>> m_meshes;
        std::vector<AssetReference<Model>> m_models;
        std::vector<AssetReference<Scene>> m_scenes;
        std::vector<AssetReference<Shader>> m_shaders;
        std::vector<AssetReference<Texture>> m_textures;

        std::vector<std::string> m_dummyMaterials;
        std::vector<std::string> m_dummyMeshes;
        std::vector<std::string> m_dummyModels;
        std::vector<std::string> m_dummyScenes;
        std::vector<std::string> m_dummyShaders;
        std::vector<std::string> m_dummyTextures;

        std::string m_error;
    };
}