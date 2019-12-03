#pragma once

#include <core/export.hpp>
#include <core/asset/asset.hpp>
#include <core/utility/path.hpp>
#include <core/utility/json.hpp>
#include <core/utility/macro.hpp>

namespace ax
{
    class AXION_CORE_API template_asset : public asset
    {
    public:
        struct parameters
        {
            path source;
            json json;
        };

    public:
        ASSET_IDENTIFIER("template")
        
        template_asset(const std::string& name, const parameters& parameters);

        json merge(const json& json) const noexcept;

    private:
        bool on_load() noexcept override;
        bool on_validate() noexcept override;
        bool on_unload() noexcept override;

    private:
        bool load_from_source(const path& path) noexcept;
        bool load_from_json(const json& json) noexcept;

        parameters m_parameters;
        json m_template;
    };
}