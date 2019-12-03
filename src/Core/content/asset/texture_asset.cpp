#include <core/content/asset/texture_asset.hpp>

#include <core/engine/engine.hpp>
#include <core/renderer/renderer_module.hpp>
#include <core/renderer/renderer_exception.hpp>
#include <core/asset/json_attributes.hpp>
#include <core/utility/json.hpp>
#include <core/utility/json_utility.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

using namespace ax;

texture_asset::texture_asset(const std::string& name, const parameters& parameters) : 
    asset(name, identifier),
    m_parameters(parameters)
{
    
}

vector2u texture_asset::get_size() const noexcept
{
    return m_size;
}
texture_asset::format texture_asset::get_format() const noexcept
{
    return m_format;
}
renderer_texture_handle texture_asset::get_handle() const noexcept
{
    return m_handle;
}

bool texture_asset::on_load() noexcept
{
    if(!m_parameters.source.empty())
    {
        return load_from_source(m_parameters.source);
    }
    else if(!m_parameters.json.is_null())
    {
        return load_from_json(m_parameters.json);
    }

    return false;
}
bool texture_asset::on_validate() noexcept
{
    try
    {
        m_handle = engine::renderer().create_texture(
            m_size,
            m_format,
            m_data
        );
    }
    catch(const renderer_exception& exception)
    {
        log_validate_error(exception.what());
        stbi_image_free(m_data);
        
        return false;
    }

    return true;
}
bool texture_asset::on_unload() noexcept
{
    try
    {
        engine::renderer().destroy_texture(m_handle);
    }
    catch(const renderer_exception& e)
    {
        log_unload_error(e.what());
        return false;
    }

    stbi_image_free(m_data);

    return true;
}

bool texture_asset::load_from_source(const path& path) noexcept
{
    int width, height, bpp;
    m_data = stbi_load(path.c_str(), &width, &height, &bpp, 0);
    if(!m_data)
    {
        log_load_error("Failed to load texture '" + path.str() + "'");
        return false;
    }

    m_size.x = width;
    m_size.y = height;

    if(bpp == 3)
        m_format = format::rgb;
    else if(bpp == 4)
        m_format = format::rgba;
    else if(bpp == 1)
        m_format = format::r;

    return true;
}
bool texture_asset::load_from_json(const json& json) noexcept
{
    path path = json_utility::read_string(json, "source");
    if(!path.empty()) return load_from_source(path);

    try
    {
        return load_from_source(json[json_attributes::source].get<std::string>());
    }
    catch(const std::exception& e)
    {
        log_load_error("Loading <" + texture_asset::identifier + "> without '" + json_attributes::source + "' attribute");
        return false;
    }
}