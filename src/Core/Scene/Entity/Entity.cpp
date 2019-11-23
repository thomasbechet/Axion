#include <Core/Scene/Entity/Entity.hpp>

#include <Core/Scene/SceneModule.hpp>
#include <Core/Builder/BuilderModule.hpp>
#include <Core/Logger/LoggerModule.hpp>

using namespace ax;

void Entity::addComponent(const std::string& identifier, const Json& json) noexcept
{
    try
    {
        Engine::builder().component.get(identifier).add(*this, json);
    }
    catch(const std::out_of_range& e)
    {
        Engine::logger().log("Failed to add component <" + identifier + "> because it was not recorded.", Severity::Warning);
    }
}

void Entity::removeComponent(const std::string& identifier) noexcept
{
    try
    {
        Engine::builder().component.get(identifier).remove(*this);
    }
    catch(const std::out_of_range& e)
    {
        Engine::logger().log("Failed to remove component <" + identifier + "> because it was not recorded.", Severity::Warning);
    }
}

void Entity::removeAllComponents() noexcept
{
    for(auto& it : m_handles)
        Engine::scene().component.destroy(it.second);
        
    m_handles.clear();
}

bool Entity::hasComponent(const std::string& identifier) const noexcept
{
    return (m_handles.find(identifier) != m_handles.end());
}

std::vector<std::reference_wrapper<Component>> Entity::getComponents() const noexcept
{
    std::vector<std::reference_wrapper<Component>> components;

    components.reserve(m_handles.size());
    for(auto it : m_handles)
        components.emplace_back(Engine::scene().component.get(it.second));

    return components;
}
std::vector<std::string> Entity::getComponentIdentifiers() const noexcept
{
    std::vector<std::string> identifiers;

    identifiers.reserve(m_handles.size());
    for(auto it : m_handles)
        identifiers.emplace_back(it.first);

    return identifiers;
}