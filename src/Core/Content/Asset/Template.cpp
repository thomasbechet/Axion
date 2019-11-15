#include <Core/Content/Asset/Template.hpp>

#include <fstream>

using namespace ax;

Template::Template(const std::string& name, const Parameters& parameters) :
    Asset(name, identifier),
    m_parameters(parameters)
{

}

Json Template::merge(const Json& json) const noexcept
{
    Json merge = m_template;
    merge.merge_patch(json);
    return merge;
}

bool Template::onLoad() noexcept
{
    if(!m_parameters.source.empty())
    {
        if(m_parameters.source.extension() != ".json")
        {
            logLoadError("Loading <" + Template::identifier + "> from file '" + m_parameters.source + "'");
            return false;
        }

        std::ifstream jsonFile(m_parameters.source.str());
        if(!jsonFile.is_open())
        {
            logLoadError("Failed to open file '" + m_parameters.source.str() + "'");
            return false;
        }
        std::string jsonBuffer{std::istreambuf_iterator<char>(jsonFile), std::istreambuf_iterator<char>()};
    
        try
        {
            Json json = Json::parse(jsonBuffer);
            return loadFromJson(json);
        }
        catch(const Json::parse_error& error)
        {
            logLoadError(error.what());
            return false;
        }
    }
    else if(!m_parameters.json.is_null())
    {
        return loadFromJson(m_parameters.json);
    }

    return false;
}
bool Template::onValidate() noexcept
{
    return true;
}
bool Template::onUnload() noexcept
{
    return true;
}

bool Template::loadFromJson(const Json& json) noexcept
{
    auto jTemplate = m_parameters.json.find("template");
    if(jTemplate != m_parameters.json.end())
    {
        m_template = *jTemplate;
        return true;
    }
    else
    {
        logLoadError("No 'template' attribute");
        return false;
    }
}