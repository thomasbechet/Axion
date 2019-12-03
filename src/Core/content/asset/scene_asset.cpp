#include <core/content/asset/scene_asset.hpp>

#include <core/utility/json_utility.hpp>
#include <core/asset/asset_module.ipp>

#include <fstream>

using namespace ax;

scene_asset::scene_asset(const std::string& name, const parameters& parameters) :
    asset(name, identifier),
    m_parameters(parameters)
{

}

scene_asset::insertion_method scene_asset::get_insertion_method() const noexcept
{
    return m_insertion_method;
}
std::string scene_asset::get_game_mode() const noexcept
{
    return m_game_mode;
}
const std::vector<std::string>& scene_asset::get_systems() const noexcept
{
    return m_systems;
}
const json& scene_asset::get_entities() const noexcept
{
    return m_entities;
}

bool scene_asset::on_load() noexcept
{
    if(!m_parameters.source.empty())
    {
        if(m_parameters.source.extension() != ".json")
        {
            log_load_error("Loading <" + scene_asset::identifier + "> from file '" + m_parameters.source + "'");
            return false;
        }

        if(json_utility::parse_file(m_parameters.source, m_parameters.json))
            return load_from_json(m_parameters.json);
        else
            return false;
    }
    else if(!m_parameters.json.is_null())
    {
        return load_from_json(m_parameters.json);
    }
    else
    {
        return false;
    }

    return true;
}
bool scene_asset::on_validate() noexcept
{
    return true;
}
bool scene_asset::on_unload() noexcept
{
    return true;
}

bool scene_asset::load_from_source(const Path& path) noexcept
{
    if(path.extension() != ".json")
    {
        log_load_error("Loading <" + scene_asset::identifier + "> from file '" + path + "'");
        return false;
    }

    if(json_utility::parse_file(path, m_parameters.json))
        return load_from_json(m_parameters.json);
    else
        return false;
}
bool scene_asset::load_from_json(const json& json) noexcept
{
    path source = json_utility::read_string(json, "source");
    if(!source.empty()) return load_from_source(source);

    //Read gamemode name
    m_gamemode = json_utility::read_string(json, "gamemode", "");
    
    //Read insertion method
    std::string insertion_method = json_utility::read_string(json, "insertion", "override");
    if(insertion_method == "override")
        m_insertion_method = insertion_method::override;
    else if(insertion_method == "additive")
        m_insertion_method = insertion_method::additive;

    //Read assets json
    auto j_assets = json.find("assets");
    if(j_assets != json.end())
    {
        if(j_assets->is_array())
        {
            try
            {
                for(auto& asset : j_assets->get<std::vector<json>>())
                    Engine::asset().load(asset);
            }
            catch(...)
            {
                log_load_error("Could not read assets from 'assets' attribute");
                return false;
            }
        }
        else
        {
            log_load_error("Attribute 'assets' is not an array");
            return false;
        }
    }

    //Read systems
    auto j_systems = json.find("systems");
    if(j_systems != json.end())
    {
        if(j_systems->is_array())
        {
            try
            {
                m_systems = j_systems->get<std::vector<std::string>>();
            }
            catch(...)
            {
                log_load_error("Could not read systems from 'systems' attribute");
                return false;
            }
        }
        else
        {
            log_load_error("Attribute 'systems' is not an array");
            return false;
        }
    }

    //Read entities
    auto j_entities = json.find("entities");
    if(j_entities != json.end())
    {
        if(j_entities->is_object())
        {
            try
            {
                m_entities = j_entities->get<json>();
            }
            catch(...)
            {
                log_load_error("Could not read entities from 'entities' attribute");
                return false;
            }
        }
        else
        {
            log_load_error("Attribute 'entities' is not an object");
            return false;
        }
    }

    return true;
}