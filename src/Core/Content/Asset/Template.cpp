#include <Core/Content/Asset/Template.hpp>

#include <Core/Utility/JsonUtility.hpp>

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
        return loadFromSource(m_parameters.source);
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

bool Template::loadFromSource(const Path& path) noexcept
{
    if(path.extension() != ".json")
    {
        logLoadError("Loading <" + Template::identifier + "> from file '" + path + "'");
        return false;
    }

    if(JsonUtility::parseFile(path, m_parameters.json))
        return loadFromJson(m_parameters.json);
    else
        return false;
}
bool Template::loadFromJson(const Json& json) noexcept
{
    Path source = JsonUtility::readString(json, "source");
    if(!source.empty()) return loadFromSource(source);

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