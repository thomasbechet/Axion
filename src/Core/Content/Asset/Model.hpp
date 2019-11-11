#pragma once

#include <Core/Export.hpp>
#include <Core/Content/Asset/Mesh.hpp>
#include <Core/Content/Asset/Material.hpp>
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
            Json json;

            bool tryDestroyMeshes = true;
            bool tryDestroyMaterials = true;
            bool tryDestroyTextures = true;

            bool asyncLoading = true;
        };

    public:
        ASSET_IDENTIFIER("model")
        
        Model(const std::string& name, const Parameters& parameters);

        const std::vector<Reference<Mesh>>& getMeshes() const noexcept;
        const std::vector<Reference<Material>>& getMaterials() const noexcept;

    private:
        bool onLoad() noexcept override;
        bool onValidate() noexcept override;
        bool onUnload() noexcept override;

    private:
        bool loadObjModel(Path path) noexcept;

    private:
        Parameters m_parameters;

        std::vector<Reference<Mesh>> m_meshes;
        std::vector<Reference<Material>> m_materials;

        std::vector<std::pair<std::string, std::string>> m_dummyModels;
    };
}