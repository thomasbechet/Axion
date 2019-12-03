#pragma once

#include <core/export.hpp>
#include <core/asset/asset.hpp>
#include <core/math/vector.hpp>
#include <core/utility/path.hpp>
#include <core/utility/types.hpp>
#include <core/utility/json.hpp>
#include <core/utility/macro.hpp>
#include <core/renderer/asset/renderer_texture.hpp>

namespace ax
{
    class AXION_CORE_API texture_asset : public asset
    {
    public:
        struct parameters
        {
            path source;
            json json;
        };

        enum Format
        {
            rgb,
            rgba,
            r,
            g,
            b
        };

    public:
        ASSET_IDENTIFIER("texture")
        
        texture_asset(const std::string& name, const parameters& parameters);

        vector2u get_size() const noexcept;
        format get_format() const noexcept;
        renderer_texture_handle get_handle() const noexcept;

    private:
        bool on_load() noexcept override;
        bool on_validate() noexcept override;
        bool on_unload() noexcept override;

    private:
        bool load_from_source(const path& path) noexcept;
        bool load_from_json(const json& json) noexcept;

        bool extract_source_from_json() noexcept;

    private:
        parameters m_parameters;

        format m_format = format::rgb;
        vector2u m_size = vector2u(0, 0);
        byte* m_data = nullptr;
        renderer_texture_handle m_handle;
    };
}