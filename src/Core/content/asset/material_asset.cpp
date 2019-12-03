#include <core/content/asset/material_asset.hpp>

#include <core/engine/engine.hpp>
#include <core/asset/asset_module.ipp>
#include <core/renderer/renderer_module.hpp>
#include <core/renderer/renderer_exception.hpp>

using namespace ax;

material_asset::material_asset(const std::string& name, const parameters& parameters) :
    asset(name, identifier),
    m_parameters(parameters)
{
    ax::content::asset::material;
}

reference<texture_asset> material_asset::get_diffuse_texture() const noexcept
{
    return m_diffuse_texture;
}
color3 material_asset::get_diffuse_color() const noexcept
{
    return m_diffuse_color;
}
void material_asset::set_diffuse_color(color3 color) noexcept
{
    m_diffuse_color = color;
    update();
}

reference<texture_asset> material_asset::get_normal_texture() const noexcept
{
    return m_normal_texture;
}

reference<texture_asset> material_asset::get_specular_texture() const noexcept
{
    return m_specular_texture;
}
float material_asset::get_specular_uniform() const noexcept
{
    return m_specular_uniform;
}
void material_asset::set_specular_uniform(float specular) noexcept
{
    m_specular_uniform = specular;
    update();
}

ax::reference<shader_asset> material_asset::get_shader() const noexcept
{
    return m_shader;
}

ax::renderer_material_handle material_asset::get_handle() const noexcept
{
    return m_handle;
}

bool material_asset::on_load() noexcept
{
    return true;
}
bool material_asset::on_validate() noexcept
{
    if(!m_parameters.diffuse_texture.empty())
        m_diffuse_texture = engine::asset().get<texture_asset>(m_parameters.diffuse_texture);
    m_diffuse_color = m_parameters.diffuse_color;

    if(!m_parameters.normal_texture.empty())
        m_normal_texture = engine::asset().get<texture_asset>(m_parameters.normal_texture);
    m_is_bump_texture = m_parameters.is_bump_texture;

    if(!m_parameters.specular_texture.empty())
        m_specular_texture = engine::asset().get<texture_asset>(m_parameters.specular_texture);
    m_specular_uniform = m_parameters.specular_uniform;

    if(!m_parameters.shader.empty())
        m_shader = engine::asset().get<shader_asset>(m_parameters.shader);

    try
    {
        //Basic parameters
        renderer_material_parameters settings;
        m_handle = engine::renderer().create_material(settings);
        update();
    }
    catch(const renderer_exception& exception)
    {
        log_validate_error(exception.what());
        return false;
    }

    return true;
}
bool material_asset::on_unload() noexcept
{
    try
    {
        if(m_parameters.try_destroy_textures)
        {
            if(m_diffuse_texture)
            {
                std::string diffuse_tex_name = m_diffuse_texture->get_name();
                m_diffuse_texture.reset();
                Engine::asset().unload<texture_asset>(diffuse_tex_name);
            }

            if(m_normal_texture)
            {
                std::string normal_tex_name = m_normal_texture->get_name();
                m_normal_texture.reset();
                Engine::asset().unload<texture_asset>(normal_tex_name);
            }

            if(m_specular_texture)
            {
                std::string specular_tex_name = m_specular_texture->get_name();
                m_specular_texture.reset();
                Engine::asset().unload<texture_asset>(specular_tex_name);
            }
        }

        if(m_parameters.try_destroy_shader)
        {
            if(m_shader)
            {
                std::string shader_name = m_shader->get_name();
                m_shader.reset();
                Engine::asset().unload<shader_asset>(shader_name);
            }
        }

        engine::renderer().destroy_material(m_handle);
    }
    catch(const renderer_exception& exception)
    {
        log_unload_error(exception.what());
        return false;
    }

    return true;
}

void material_asset::update() noexcept
{
    //Configure renderer material settings
    renderer_material_parameters settings;

    //Diffuse
    settings.diffuse_texture = (m_diffuse_texture) ? m_diffuse_texture->getHandle() : 0;
    settings.diffuse_color = m_diffuse_color;
    settings.use_diffuse_texture = (m_diffuse_texture.isValid());

    //Normal
    settings.normal_texture = (m_normal_texture) ? m_normal_texture->getHandle() : 0;
    settings.use_normal_texture = (m_normal_texture.isValid());
    settings.is_bump_texture = m_is_bump_texture;

    //Specular
    settings.specular_texture = (m_specular_texture) ? m_specular_texture->getHandle() : 0;
    settings.specular_uniform = m_specular_uniform;
    settings.use_specular_texture = (m_specular_texture.isValid());       

    //Shader
    settings.shader = (m_shader) ? m_shader->get_handle() : 0;

    try
    {
        m_handle->update(settings);
    }
    catch(const renderer_exception& e)
    {
        engine::logger().log("Failed to update asset <" + material_asset::identifier + "> '" + get_name() + "'", severity::warning);
    }
}