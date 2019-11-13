#include <Core/Content/Asset/Scene.hpp>

#include <fstream>

using namespace ax;

Scene::Scene(const std::string& name, const Parameters& parameters) :
    Asset(name, identifier),
    m_parameters(parameters)
{

}

Scene::InsertionMethod Scene::getInsertionMethod() const noexcept
{
    return m_insertionMethod;
}
std::string Scene::getGameMode() const noexcept
{
    return m_gameMode;
}
const std::vector<std::string>& Scene::getSystems() const noexcept
{
    return m_systems;
}
const std::vector<Json>& Scene::getEntities() const noexcept
{
    return m_entities;
}

bool Scene::onLoad() noexcept
{
    if(!m_parameters.source.empty())
    {
        if(m_parameters.source.extension() != ".json")
        {
            logLoadError("Loading <" + Scene::identifier + "> from file '" + m_parameters.source + "'");
            return false;
        }

        std::ifstream jsonFile(m_parameters.source.str());
        if(!jsonFile.is_open())
        {
            logLoadError("Failed to open file '" + m_parameters.source.str() + "'");
            return false;
        }
        std::string jsonBuffer{std::istreambuf_iterator<char>(jsonFile), std::istreambuf_iterator<char>()};

        //Parse json
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
    else
    {
        return false;
    }

    return true;
}
bool Scene::onValidate() noexcept
{
    return true;
}
bool Scene::onUnload() noexcept
{
    return true;
}

bool Scene::loadFromJson(const Json& json) noexcept
{
    

    return true;
}