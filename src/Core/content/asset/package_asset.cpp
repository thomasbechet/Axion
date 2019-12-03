#include <core/content/asset/package_asset.hpp>

#include <core/engine/engine.hpp>
#include <core/asset/asset_module.ipp>
#include <core/asset/json_attributes.hpp>
#include <core/utility/json.hpp>
#include <core/utility/json_utility.hpp>

#include <fstream>

using namespace ax;

package_asset::package_asset(const std::string& name, const parameters& parameters) :
    asset(name, identifier),
    m_parameters(parameters)
{

}

bool package_asset::on_load() noexcept
{
    if(!m_parameters.source.empty())
    {
        return load_from_source(m_parameters.source);
    }
    else if(!m_parameters.json.is_null())
    {
        return load_from_json(m_parameters.json);
    }
    else
    {
        return false;
    }
}
bool package_asset::on_validate() noexcept
{
    for(auto& it : m_assets)
        std::get<2>(it) = Engine::asset().get(std::get<0>(it), std::get<1>(it));

    return true;
}
bool package_asset::on_unload() noexcept
{
    for(auto& it : m_assets)
    {
        Engine::asset().unload(
            std::get<0>(it),
            std::get<1>(it)
        );
        std::get<2>(it).reset();
    }
    m_assets.clear();

    return true;
}

bool package_asset::load_from_source(const Path& path) noexcept
{
    if(path.extension() != ".json")
    {
        log_load_error("Loading <" + package_asset::identifier + "> from file '" + path + "'");
        return false;
    }

    if(json_utility::parse_file(path, m_parameters.json))
        return load_from_json(m_parameters.json);
    else
        return false;
}
bool package_asset::load_from_json(const Json& json) noexcept
{
    path source = json_utility::read_string(json, "source");
    if(!source.empty()) return load_from_source(source);

    try
    {
        auto j_assets = json[json_attributes::assets];
        if(!j_assets.is_array())
        {
            log_load_error("Invalid '" + json_attributes::assets + "' attribute");
            return false;
        }

        //Load each items
        for(auto& item : j_assets)
        {
            if(m_parameters.async_loading)
                engine::asset().load_async(item);
            else
                Engine::asset().load(item);

            //Should not throw exceptions related to missing name of type attribute because
            //json loading method already ensure there are those attributes.
            m_assets.emplace_back(std::make_tuple(
                item[json_attributes::type].get<std::string>(),
                item[json_attributes::name].get<std::string>(),
                basic_reference()
            ));

            //TODO dispatched async loading
        }
    }
    catch(const std::exception& e)
    {
        log_load_error("Loading <" + package_asset::identifier + "> without '" + json_attributes::assets + "' attribute");
        return false;
    }

    return true;
}