#pragma once

/////////////////
//HEADERS
/////////////////
#include <Core/Export.hpp>
#include <Core/Context/Game.hpp>
#include <Core/Logger/Logger.hpp>
#include <Core/Entity/ComponentManager.hpp>

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
                Game::interrupt("Entity [id " + std::to_string(m_id) + "] already owns component <" + C::name() + ">");

            ComponentHandle handle = Game::components().create<C>(args...);
            m_handles.emplace_back(handle);

            return Game::components().get<C>(handle);
        }
        template<typename C>
        void removeComponent() noexcept
        {
            unsigned section = Game::components().componentSection<C>();
            for(auto it = m_handles.begin(); it != m_handles.end(); it++)
                if(it->section == section)
                {
                    Game::components().destroyComponent(*it);
                    m_handles.erase(it);
                    return;
                }

            ax::Game::logger().log("Try to remove nonexistent component <" + C::name() + "> from Entity [id=" + std::to_string(m_id) + "]", Logger::WARNING);
        }
        void removeAll() noexcept
        {
            for(auto it = m_handles.begin(); it != m_handles.end(); it++)
            {
                Game::components().destroyComponent(*it);
            }
            m_handles.clear();
        }

        template<typename C>
        C& getComponent() const noexcept
        {
            unsigned section = Game::components().componentSection<C>();
            for(auto it = m_handles.begin(); it != m_handles.end(); it++){
                if(it->section == section) return Game::components().get<C>(*it);
            }

            Game::interrupt("Component <" + C::name() + "> from entity [id " + std::to_string(m_id) + "] doesn't exist");
        }

        template<typename C>
        bool hasComponent() const noexcept
        {
            unsigned section = Game::components().componentSection<C>();
            for(auto it = m_handles.begin(); it != m_handles.end(); it++)
                if(it->section == section) return true;

            return false;
        }

    private:
        std::vector<ComponentHandle> m_handles;
        unsigned m_id = 0;
    };
}