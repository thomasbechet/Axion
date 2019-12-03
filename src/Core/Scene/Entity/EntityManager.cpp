#include <Core/Scene/Entity/EntityManager.hpp>

#include <Core/Asset/AssetModule.ipp>
#include <Core/Builder/BuilderModule.hpp>
#include <Core/Content/Asset/TemplateAsset.hpp>
#include <Core/Utility/JsonUtility.hpp>
#include <Core/Scene/Entity/Entity.ipp>

#include <string>

using namespace ax;

Entity& EntityManager::create() noexcept
{
    Id id = m_chunks.add();
    Entity& entity = m_chunks.get(id);
    entity.m_id = id;

    return entity;
}
Entity& EntityManager::create(const std::string& name) noexcept
{
    Entity& entity = create();
    m_tagTable.emplace(name, entity);

    return entity;
}
Entity& EntityManager::create(const std::string& key, const Json& json) noexcept
{
    Entity& entity = create();

    Json body;

    std::string templateAsset = JsonUtility::readString(json, "template");
    if(!templateAsset.empty())
    {
        body = Engine::asset().get<TemplateAsset>(templateAsset)->merge(json);
        body.erase("template");
    }
    else
    {
        body = json;
    }
    
    if(JsonUtility::readBoolean(body, "tagged", false)) 
    {
        m_tagTable.emplace(key, entity);
        body.erase("tagged");
    }

    for(auto& [key, item] : body.items())
        addRecursive(entity, body, key, item);

    return entity;
}

void EntityManager::destroy(Entity& entity) noexcept
{
    entity.removeAllComponents();
    m_chunks.remove(entity.m_id);
}
void EntityManager::destroy(const std::string& name) noexcept
{
    destroy(m_tagTable.at(name).get());
}
void EntityManager::destroyAll() noexcept
{
    for(auto& entity : m_chunks)
        entity.removeAllComponents();

    m_chunks.clear();
}

Entity& EntityManager::get(const std::string& name) noexcept
{
    return m_tagTable.at(name).get();
}

void EntityManager::addRecursive(Entity& entity, Json& body, const std::string& key, const Json& item)
{
    for(auto requirement : Engine::builder().component.get(key).requirements())
    {
        if(!entity.hasComponent(requirement))
        {
            auto it = body.find(requirement);
            if(it != body.end())
            {
                addRecursive(entity, body, requirement, *it);
            }
            else
            {
                Engine::logger().log("Component requirement from '" + key + "' not satisfied. Missing '" + requirement + "'", Severity::Warning);
            }
        }
    }

    entity.addComponent(key, item);
    body.erase(key);
}