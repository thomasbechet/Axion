#include <Core/Content/Asset/Package.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Asset/AssetModule.ipp>
#include <Core/Asset/JsonAttributes.hpp>
#include <Core/Utility/Json.hpp>
#include <Core/Utility/JsonUtility.hpp>

#include <fstream>

using namespace ax;

Package::Package(const std::string& name, const Parameters& parameters) :
    Asset(name, identifier),
    m_parameters(parameters)
{

}

bool Package::onLoad() noexcept
{
    if(!m_parameters.source.empty())
    {
        return loadFromSource(m_parameters.source);
    }
    else if(!m_parameters.json.is_null())
    {
        return loadFromJson(m_parameters.json);
    }
    else
    {
        return false;
    }
}
bool Package::onValidate() noexcept
{
    for(auto& it : m_assets)
        std::get<2>(it) = Engine::asset().get(std::get<0>(it), std::get<1>(it));

    return true;
}
bool Package::onUnload() noexcept
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

bool Package::loadFromSource(const Path& path) noexcept
{
    if(path.extension() != ".json")
    {
        logLoadError("Loading <" + Package::identifier + "> from file '" + path + "'");
        return false;
    }

    if(JsonUtility::parseFile(path, m_parameters.json))
        return loadFromJson(m_parameters.json);
    else
        return false;
}
bool Package::loadFromJson(const Json& json) noexcept
{
    Path source = JsonUtility::readString(json, "source");
    if(!source.empty()) return loadFromSource(source);

    try
    {
        auto jAssets = json[JsonAttributes::assets];
        if(!jAssets.is_array())
        {
            logLoadError("Invalid '" + JsonAttributes::assets + "' attribute");
            return false;
        }

        //Load each items
        for(auto& item : jAssets)
        {
            if(m_parameters.asyncLoading)
                Engine::asset().loadAsync(item);
            else
                Engine::asset().load(item);

            //Should not throw exceptions related to missing name of type attribute because
            //json loading method already ensure there are those attributes.
            m_assets.emplace_back(std::make_tuple(
                item[JsonAttributes::type].get<std::string>(),
                item[JsonAttributes::name].get<std::string>(),
                BasicReference()
            ));

            //TODO dispatched async loading
        }
    }
    catch(const std::exception& e)
    {
        logLoadError("Loading <" + Package::identifier + "> without '" + JsonAttributes::assets + "' attribute");
        return false;
    }

    return true;
}