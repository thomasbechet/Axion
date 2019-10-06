#pragma once

#include <Core/Export.hpp>
#include <Core/Asset/Asset/Texture.hpp>
#include <Core/Asset/Asset/Mesh.hpp>
#include <Core/Asset/Asset/Material.hpp>
#include <Core/Asset/Asset/Model.hpp>
#include <Core/Asset/Asset/Shader.hpp>
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
            std::string json;
            bool asyncLoading = false;
        };

    public:
        static const std::string name;

        Package(std::string name, const Parameters& parameters);

        const std::vector<AssetReference<Texture>>& getTextures() const noexcept;
        const std::vector<AssetReference<Mesh>>& getMeshes() const noexcept;
        const std::vector<AssetReference<Material>>& getMaterials() const noexcept;
        const std::vector<AssetReference<Model>>& getModels() const noexcept;
        const std::vector<AssetReference<Shader>>& getShaders() const noexcept;

    private:
        bool onLoad() noexcept override;
        bool onValidate() noexcept override;
        bool onUnload() noexcept override;
        void onError() noexcept override;

    private:
        bool loadFromJsonAsync(std::string& json) noexcept;

    private:
        Parameters m_parameters;

        std::vector<AssetReference<Texture>> m_textures;
        std::vector<AssetReference<Mesh>> m_meshes;
        std::vector<AssetReference<Material>> m_materials;
        std::vector<AssetReference<Model>> m_models;
        std::vector<AssetReference<Shader>> m_shaders;

        std::vector<std::string> m_dummyTextures;
        std::vector<std::string> m_dummyMeshes;
        std::vector<std::string> m_dummyMaterials;
        std::vector<std::string> m_dummyModels;
        std::vector<std::string> m_dummyShaders;

        std::string m_error;
    };
}