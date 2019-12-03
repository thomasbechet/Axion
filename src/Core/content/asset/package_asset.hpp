#pragma once

#include <core/export.hpp>
#include <core/asset/asset.hpp>
#include <core/utility/reference.hpp>
#include <core/content/asset/material_asset.hpp>
#include <core/content/asset/mesh_asset.hpp>
#include <core/content/asset/model_asset.hpp>
#include <core/content/asset/scene_asset.hpp>
#include <core/content/asset/shader_asset.hpp>
#include <core/content/asset/texture_asset.hpp>

#include <string>
#include <memory>
#include <vector>

namespace ax
{
    class AXION_CORE_API package_asset : public asset
    {
    public:
        struct parameters
        {
            path source;
            json json;
            bool async_loading = true;
        };

    public:
        ASSET_IDENTIFIER("package")
        
        package_asset(const std::string& name, const parameters& parameters);

    private:
        bool on_load() noexcept override;
        bool on_validate() noexcept override;
        bool on_unload() noexcept override;

    private:
        bool load_from_source(const Path& path) noexcept;
        bool load_from_json(const Json& json) noexcept;

    private:
        parameters m_parameters;

        using item = std::tuple<std::string, std::string, basic_reference>;
        std::vector<item> m_assets;
    };
}