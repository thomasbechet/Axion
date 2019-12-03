#pragma once

#include <core/export.hpp>
#include <core/content/asset/mesh_asset.hpp>
#include <core/content/asset/material_asset.hpp>
#include <core/utility/path.hpp>

#include <string>
#include <vector>

namespace ax
{
    class AXION_CORE_API model_asset : public asset
    {
    public:
        struct parameters
        {
            path source;
            json json;

            bool try_destroy_meshes = true;
            bool try_destroy_materials = true;
            bool try_destroy_textures = true;

            bool async_loading = true;
        };

    public:
        ASSET_IDENTIFIER("model")
        
        model_asset(const std::string& name, const parameters& parameters);

        const std::vector<reference<mesh_asset>>& get_meshes() const noexcept;
        const std::vector<reference<material_asset>>& get_materials() const noexcept;

    private:
        bool on_load() noexcept override;
        bool on_validate() noexcept override;
        bool on_unload() noexcept override;

    private:
        bool load_from_source(const path& path) noexcept;
        bool load_from_json(const json& json) noexcept;
        bool load_obj_model(const path& path) noexcept;

    private:
        parameters m_parameters;

        std::vector<reference<mesh_asset>> m_meshes;
        std::vector<reference<material_asset>> m_materials;

        std::vector<std::pair<std::string, std::string>> m_dummy_models;
    };
}