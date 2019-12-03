#include <core/content/asset/shader_asset.hpp>

#include <Core/engine/engine.hpp>
#include <core/renderer/renderer_module.hpp>
#include <core/renderer/renderer_exception.hpp>
#include <core/asset/json_attributes.hpp>
#include <core/utility/json.hpp>
#include <core/utility/json_utility.hpp>

#include <fstream>
#include <streambuf>

using namespace ax;

shader_asset::shader_asset(const std::string& name, const parameters& parameters) :
    asset(name, identifier),
    m_parameters(parameters)
{

}

std::string shader_asset::get_vertex_code() const noexcept
{
    return m_vertex;
}
std::string shader_asset::get_fragment_code() const noexcept
{
    return m_fragment;
}

renderer_shader_handle shader_asset::get_handle() const noexcept
{
    return m_handle;
}

bool shader_asset::on_load() noexcept
{
    Json json;
    if(!m_parameters.source.empty())
    {
        if(!json_utility::parse_file(m_parameters.source, json)) return false;
    }
    else
    {
        json = m_parameters.json;
    }

    try
    {
        auto j_vertex = json[json_attributes::vertex];
        try
        {
            auto j_fragment = json[json_attributes::fragment];

            path vertex = j_vertex.get<std::string>();
            path fragment = j_fragment.get<std::string>();

            std::ifstream vertex_file(vertex.str());
            if(!vertex_file.is_open())
            {
                log_load_error("Failed to open file '" + vertex.str() + "'");
                return false;
            }
            m_vertex.assign(
                (std::istreambuf_iterator<char>(vertex_file)),
                (std::istreambuf_iterator<char>())
            );

            std::ifstream fragment_file(fragment.str());
            if(!fragment_file.is_open())
            {
                log_load_error("Failed to open file '" + fragment.str() + "'");
                return false;
            }
            m_fragment.assign(
                (std::istreambuf_iterator<char>(fragment_file)),
                (std::istreambuf_iterator<char>())
            );
        }
        catch(const std::exception& e)
        {
            log_load_error("Loading <" + shader_asset::identifier + "> without '" + json_attributes::fragment + "' attribute");
            return false;
        }
    }
    catch(const std::exception& e)
    {
        log_load_error("Loading <" + shader_asset::identifier + "> without '" + json_attributes::vertex + "' attribute");
        return false;
    }

    return true;
}
bool shader_asset::on_validate() noexcept
{
    try
    {
        m_handle = engine::renderer().create_shader(&m_vertex, &m_fragment);
    }
    catch(const renderer_exception& exception)
    {     
        log_validate_error(exception.what());
        return false;
    }

    return true;
}
bool shader_asset::on_unload() noexcept
{
    try
    {
        engine::renderer().destroy_shader(m_handle);
    }
    catch(const renderer_exception& exception)
    {
        log_unload_error(exception.what());
        return false;
    }

    return true;
}
