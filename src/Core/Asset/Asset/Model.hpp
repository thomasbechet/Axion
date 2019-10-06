#pragma once

#include <Core/Export.hpp>
#include <Core/Asset/Asset/Mesh.hpp>
#include <Core/Asset/Asset/Material.hpp>
#include <Core/Utility/Path.hpp>

#include <string>
#include <vector>

namespace ax
{
    class AXION_CORE_API Model : public Asset
    {
    public:
        struct Parameters
        {
            Path source;
            std::string json;

            bool tryDestroyMeshes = true;
            bool tryDestroyMaterials = true;
            bool tryDestroyTextures = true;
        };

    public:
        static const std::string name;

        Model(std::string name, const Parameters& parameters);

        const std::vector<AssetReference<Mesh>>& getMeshes() const noexcept;
        const std::vector<AssetReference<Material>>& getMaterials() const noexcept;

    private:
        bool onLoad() noexcept override;
        bool onValidate() noexcept override;
        bool onUnload() noexcept override;
        void onError() noexcept override;

    private:
        bool loadObjModelAsync(Path path) noexcept;

    private:
        Parameters m_parameters;

        std::vector<AssetReference<Mesh>> m_meshes;
        std::vector<AssetReference<Material>> m_materials;

        std::vector<std::pair<std::string, std::string>> m_dummyModels;

        std::string m_error;
    };
}