#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Reference.hpp>
#include <Core/Asset/Asset/Material.hpp>
#include <Core/Asset/Asset/Mesh.hpp>
#include <Core/Asset/Asset/Model.hpp>
#include <Core/Asset/Asset/Scene.hpp>
#include <Core/Asset/Asset/Shader.hpp>
#include <Core/Asset/Asset/Texture.hpp>
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

    private:
        bool onLoad() noexcept override;
        bool onValidate() noexcept override;
        bool onUnload() noexcept override;

    private:
        bool loadFromJson(Json& json) noexcept;

    private:
        Parameters m_parameters;

        std::vector<Reference<Material>> m_materials;
        std::vector<Reference<Mesh>> m_meshes;
        std::vector<Reference<Model>> m_models;
        std::vector<Reference<Scene>> m_scenes;
        std::vector<Reference<Shader>> m_shaders;
        std::vector<Reference<Texture>> m_textures;

        std::vector<std::string> m_dummyMaterials;
        std::vector<std::string> m_dummyMeshes;
        std::vector<std::string> m_dummyModels;
        std::vector<std::string> m_dummyScenes;
        std::vector<std::string> m_dummyShaders;
        std::vector<std::string> m_dummyTextures;
    };
}