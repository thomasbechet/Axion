#include <core/content/asset/template_asset.hpp>

#include <core/utility/json_utility.hpp>

#include <fstream>

using namespace ax;

template_asset::template_asset(const std::string& name, const parameters& parameters) :
    asset(name, identifier),
    m_parameters(parameters)
{

}

json template_asset::merge(const json& json) const noexcept
{
    json merge = m_template;
    merge.merge_patch(json);
    return merge;
}

bool template_asset::on_load() noexcept
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
bool template_asset::on_validate() noexcept
{
    return true;
}
bool template_asset::on_unload() noexcept
{
    return true;
}

bool template_asset::load_from_source(const path& path) noexcept
{
    if(path.extension() != ".json")
    {
        log_load_error("Loading <" + template_asset::identifier + "> from file '" + path + "'");
        return false;
    }

    if(json_utility::parse_file(path, m_parameters.json))
        return load_from_json(m_parameters.json);
    else
        return false;
}
bool template_asset::load_from_json(const json& json) noexcept
{
    path source = json_utility::read_string(json, "source");
    if(!source.empty()) return load_from_source(source);

    auto j_template = m_parameters.json.find("template");
    if(j_template != m_parameters.json.end())
    {
        m_template = *j_template;
        return true;
    }
    else
    {
        log_load_error("No 'template' attribute");
        return false;
    }
}