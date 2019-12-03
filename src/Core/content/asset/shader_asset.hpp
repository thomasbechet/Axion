#pragma once

#include <core/export.hpp>
#include <core/asset/asset.hpp>
#include <core/utility/path.hpp>
#include <core/utility/json.hpp>
#include <core/utility/macro.hpp>
#include <core/renderer/asset/renderer_shader.hpp>

namespace ax
{
    class AXION_CORE_API shader_asset : public asset
    {
    public:
        struct parameters
        {
            path source;
            json json;
        };

    public:
        ASSET_IDENTIFIER("shader")
        
        shader_asset(const std::string& name, const parameters& parameters);

        std::string get_vertex_code() const noexcept;
        std::string get_fragment_code() const noexcept;

        renderer_shader_handle get_handle() const noexcept;

    private:
        bool on_load() noexcept override;
        bool on_validate() noexcept override;
        bool on_unload() noexcept override;

    private:
        parameters m_parameters;

        std::string m_vertex;
        std::string m_fragment;

        renderer_shader_handle m_handle;
    };
}