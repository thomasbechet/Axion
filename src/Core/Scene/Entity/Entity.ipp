#pragma once

#include <Core/Scene/Entity/Entity.hpp>

#include <Core/Engine/Engine.hpp>
#include <Core/Logger/LoggerModule.hpp>
#include <Core/Scene/SceneModule.hpp>
#include <Core/Scene/Component/ComponentManager.hpp>
#include <Core/Scene/Component/ComponentManager.ipp>

namespace ax
{
    template<typename C, typename... Args>
    C& Entity::addComponent(Args&&... args) noexcept
    {
        if(hasComponent<C>())
            Engine::interrupt("Entity [id " + std::to_string(m_id) + "] already owns component <" + C::identifier + ">");

        ComponentHandle handle = Engine::scene().component.create<C>(*this, args...);
        m_handles.emplace(C::identifier, handle);

        return Engine::scene().component.get<C>(handle);
    }
    template<typename C>
    void Entity::removeComponent() noexcept
    {
        try
        {
            Engine::scene().component.destroy(m_handles.at(C::identifier));
            m_handles.erase(C::identifier);
        }
        catch(const std::out_of_range& e)
        {
            Engine::logger().log("Try to remove nonexistent component <" + C::identifier + "> from Entity [id=" + std::to_string(m_id) + "]", Severity::Warning);
        }        
    }
    template<typename C>
    C& Entity::getComponent() const noexcept
    {
        try
        {
            return Engine::scene().component.get<C>(m_handles.at(C::identifier));
        }
        catch(const std::out_of_range& e)
        {
            Engine::interrupt("Component <" + C::identifier + "> from entity [id " + std::to_string(m_id) + "] doesn't exist");
        }
    }
    template<typename C>
    bool Entity::hasComponent() const noexcept
    {
        return (m_handles.find(C::identifier) != m_handles.end());
    }
}