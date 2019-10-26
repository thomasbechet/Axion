#pragma once

#include <Core/Scene/Entity/Entity.hpp>

#include <Core/Context/Engine.hpp>
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
            Engine::interrupt("Entity [id " + std::to_string(m_id) + "] already owns component <" + C::type + ">");

        ComponentHandle handle = Engine::scene().component.create<C>(const_cast<const Entity&>(*this), args...);
        m_handles.emplace_back(handle);

        return Engine::scene().component.get<C>(handle);
    }
    template<typename C>
    void Entity::removeComponent() noexcept
    {
        unsigned section = Engine::scene().component.componentSection<C>();
        for(auto it = m_handles.begin(); it != m_handles.end(); it++)
        {
            if(it->section == section)
            {
                Engine::scene().component.destroy(*it);
                m_handles.erase(it);
                return;
            }
        }

        Engine::logger().log("Try to remove nonexistent component <" + C::type + "> from Entity [id=" + std::to_string(m_id) + "]", Severity::Warning);
    }
    template<typename C>
    C& Entity::getComponent() const noexcept
    {
        unsigned section = Engine::scene().component.componentSection<C>();
        for(auto& it : m_handles)
            if(it.section == section) return Engine::scene().component.get<C>(it);

        Engine::interrupt("Component <" + C::type + "> from entity [id " + std::to_string(m_id) + "] doesn't exist");
    }
    template<typename C>
    bool Entity::hasComponent() const noexcept
    {
        unsigned section = Engine::scene().component.componentSection<C>();
        for(auto& it : m_handles)
            if(it.section == section) return true;
            
        return false;
    }
}