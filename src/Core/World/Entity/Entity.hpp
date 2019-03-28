#pragma once

#include <Core/Export.hpp>
#include <Core/Context/Engine.hpp>
#include <Core/Logger/Logger.hpp>
#include <Core/World/Component/Component.hpp>
#include <Core/World/Component/ComponentManager.hpp>
#include <Core/World/World.hpp>

namespace ax
{
    class AXION_CORE_API Entity
    {
    public:
        friend class EntityManager;

    public:
        template<typename C, typename... Args>
        C& addComponent(Args&&... args) noexcept
        {
            if(hasComponent<C>())
                Engine::interrupt("Entity [id " + std::to_string(m_id) + "] already owns component <" + C::name + ">");

            ComponentHandle handle = Engine::world().component.create<C>(args...);
            m_handles.emplace_back(handle);

            return Engine::world().component.get<C>(handle);
        }
        template<typename C>
        void removeComponent() noexcept
        {
            unsigned section = Engine::world().component.componentSection<C>();
            for(auto it = m_handles.begin(); it != m_handles.end(); it++)
            {
                if(it->section == section)
                {
                    Engine::world().component.destroyComponent(*it);
                    m_handles.erase(it);
                    return;
                }
            }

            Engine::logger().log("Try to remove nonexistent component <" + C::name + "> from Entity [id=" + std::to_string(m_id) + "]", Logger::Warning);
        }
        void removeAll() noexcept
        {
            for(auto& it : m_handles)
                Engine::world().component.destroyComponent(it);
                
            m_handles.clear();
        }
        template<typename C>
        C& getComponent() const noexcept
        {
            unsigned section = Engine::world().component.componentSection<C>();
            for(auto& it : m_handles){
                if(it.section == section) return Engine::world().component.get<C>(it);
            }

            Engine::interrupt("Component <" + C::name + "> from entity [id " + std::to_string(m_id) + "] doesn't exist");
        }
        template<typename C>
        bool hasComponent() const noexcept
        {
            unsigned section = Engine::world().component.componentSection<C>();
            for(auto& it : m_handles)
                if(it.section == section) return true;
                
            return false;
        }

    private:
        std::vector<ComponentHandle> m_handles;
        unsigned m_id = 0;
    };
}