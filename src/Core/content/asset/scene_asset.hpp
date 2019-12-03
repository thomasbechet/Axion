#pragma once

#include <core/export.hpp>
#include <core/asset/asset.hpp>
#include <core/utility/path.hpp>
#include <core/utility/json.hpp>
#include <core/utility/macro.hpp>

#include <string>

namespace ax
{
    class AXION_CORE_API scene_asset : public asset
    {
    public:
        struct parameters
        {
            path source;
            json json;
        };

        enum insertion_method
        {
            override,
            additive
        };

    public:
        ASSET_IDENTIFIER("scene")
        
        scene_asset(const std::string& name, const parameters& parameters);

        insertion_method getinsertion_method() const noexcept;
        std::string get_game_mode() const noexcept;
        const std::vector<std::string>& get_systems() const noexcept;
        const json& get_entities() const noexcept;

    private:
        bool on_load() noexcept override;
        bool on_validate() noexcept override;
        bool on_unload() noexcept override;

    private:
        bool load_from_source(const path& path) noexcept;
        bool load_from_json(const json& json) noexcept;

        parameters m_parameters;

        insertion_method m_insertion_method;
        std::string m_gamemode;
        std::vector<std::string> m_systems;
        json m_entities;
    };
}