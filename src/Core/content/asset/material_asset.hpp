#pragma once

#include <core/export.hpp>
#include <core/utility/color.hpp>
#include <core/utility/reference.ipp>
#include <core/content/asset/texture_asset.hpp>
#include <core/content/asset/shader_asset.hpp>
#include <core/renderer/asset/renderer_material.hpp>

namespace ax
{
    class AXION_CORE_API material_asset : public asset
    {
    public:
        struct parameters
        {
            path source;
            json json;

            bool try_destroy_textures = true;
            bool try_destroy_shader = true;

            std::string diffuse_texture = "";
            color3 diffuse_color = color3(1.0f, 1.0f, 1.0f);
            
            std::string normal_texture = "";
            bool is_bump_texture = false;

            std::string specular_texture = "";
            float specular_uniform = 0.5f;

            std::string shader = "";
        };

    public:
        static inline const std::string blank = "default_material";

        ASSET_IDENTIFIER("material")

        material_asset(const std::string& name, const parameters& parameters);

        reference<texture_asset> get_diffuse_texture() const noexcept;
        Color3 get_diffuse_color() const noexcept;
        void set_diffuse_color(color3 color) noexcept;

        reference<texture_asset> get_normal_texture() const noexcept;

        reference<texture_asset> get_specular_texture() const noexcept;
        float get_specular_uniform() const noexcept;
        void set_specular_uniform(float specular) noexcept;

        reference<shader_asset> get_shader() const noexcept;

        renderer_material_handle get_handle() const noexcept;

    private:
        bool on_load() noexcept override;
        bool on_validate() noexcept override;
        bool on_unload() noexcept override;

    private:
        void update() noexcept;

    private:
        parameters m_parameters;

        reference<texture_asset> m_diffuse_texture;
        color3 m_diffuse_color = color3(1.0f, 1.0f, 1.0f);
        
        reference<texture_asset> m_normal_texture;
        bool m_is_bump_texture = false;

        reference<texture_asset> m_specular_texture;
        float m_specular_uniform = 1.0f;

        reference<shader_asset> m_shader;

        renderer_material_handle m_handle;
    };
}