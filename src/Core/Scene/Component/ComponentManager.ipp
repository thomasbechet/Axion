#pragma once

#include <Core/Scene/Component/ComponentManager.hpp>

#include <Core/Scene/Component/ComponentList.ipp>

#include <typeinfo>

namespace ax
{
    template<typename C>
    size_t ComponentManager::getSection() noexcept
    {
        std::type_index index = std::type_index(typeid(C));

        if(m_indexes.find(index) != m_indexes.end())
            return m_indexes.at(index);

        m_componentLists.emplace_back(std::make_unique<ComponentList<C>>());
        m_indexes[index] = m_componentLists.size() - 1;

        return m_componentLists.size() - 1;
    }

    template<typename C>
    size_t ComponentManager::componentSection() noexcept
    {
        static size_t section = getSection<C>();
        return section;
    }

    template<typename C, typename... Args>
    ComponentHandle ComponentManager::create(Entity& entity, Args&&... args) noexcept
    {
        ComponentHandle handle;
        unsigned section = componentSection<C>();
        handle.offset = static_cast<ComponentList<C>&>(*m_componentLists.at(section).get()).create(entity, args...);
        handle.section = section;

        return handle;
    }

    template<typename C>
    C& ComponentManager::get(ComponentHandle handle) noexcept
    {
        return static_cast<ComponentList<C>&>(*m_componentLists.at(handle.section).get()).get(handle.offset);
    }

    template<typename C>
    ComponentList<C>& ComponentManager::list() noexcept
    {
        return static_cast<ComponentList<C>&>(*m_componentLists.at(componentSection<C>()).get());
    }
}