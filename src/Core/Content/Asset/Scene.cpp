#include <Core/Content/Asset/Scene.hpp>

#include <Core/Utility/JsonUtility.hpp>

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
    //Read gamemode name
    m_gameMode = JsonUtility::readString(json, "gamemode", "");
    
    //Read insertion method
    std::string insertionMethod = JsonUtility::readString(json, "insertion", "override");
    if(insertionMethod == "override")
        m_insertionMethod = InsertionMethod::Override;
    else if(insertionMethod == "additive")
        m_insertionMethod = InsertionMethod::Additive;

    //Read assets json
    auto jAssets = json.find("assets");
    if(jAssets != json.end())
    {
        if(jAssets->is_array())
        {
            try
            {
                m_assets = jAssets->get<std::vector<Json>>();
            }
            catch(...)
            {
                logLoadError("Could not read assets from 'assets' attribute");
                return false;
            }
        }
        else
        {
            logLoadError("Attribute 'assets' is not an array");
            return false;
        }
    }

    //Read systems
    auto jSystems = json.find("systems");
    if(jSystems != json.end())
    {
        if(jSystems->is_array())
        {
            try
            {
                m_systems = jSystems->get<std::vector<std::string>>();
            }
            catch(...)
            {
                logLoadError("Could not read systems from 'systems' attribute");
                return false;
            }
        }
        else
        {
            logLoadError("Attribute 'systems' is not an array");
            return false;
        }
    }

    //Read entities
    auto jEntities = json.find("entities");
    if(jEntities != json.end())
    {
        if(jEntities->is_array())
        {
            try
            {
                m_entities = jEntities->get<std::vector<Json>>();
            }
            catch(...)
            {
                logLoadError("Could not read entities from 'entities' attribute");
                return false;
            }
        }
        else
        {
            logLoadError("Attribute 'entities' is not an array");
            return false;
        }
    }

    return true;
}