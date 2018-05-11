#pragma once 

/////////////////
//HEADERS
/////////////////
#include <vector>
#include <memory>
#include <Core/Export.hpp>
#include <Core/Utility/NonCopyable.hpp>
#include <Core/Entity/Component.hpp>
#include <Core/Entity/ComponentList.hpp>

#include <iostream>

namespace ax
{
    class AXION_CORE_API ComponentManager : public NonCopyable
    {
    private:
        template<typename C>
        size_t generateNewSection() noexcept
        {
            m_componentLists.emplace_back(std::make_unique<ComponentList<C>>());
            return m_componentLists.size() - 1;
        }

    public:
        template<typename C>
        size_t componentSection() noexcept
        {
            static size_t section = generateNewSection<C>();
            return section;
        }

        template<typename C, typename... Args>
        ComponentHandle createComponent(Args&&... args) noexcept
        {
            ComponentHandle handle;
            unsigned section = componentSection<C>();
            handle.offset = static_cast<ComponentList<C>&>(*m_componentLists[section].get()).create(args...);
            handle.section = section;

            return handle;
        }

        void destroyComponent(ComponentHandle handle) noexcept
        {
            m_componentLists[handle.section].get()->destroy(handle.offset);
        }

        template<typename C>
        C& getComponent(ComponentHandle handle) noexcept
        {
            return static_cast<ComponentList<C>&>(*m_componentLists[handle.section].get()).get(handle.offset);
        }

        template<typename C>
        ComponentList<C>& getComponentList() noexcept
        {
            return static_cast<ComponentList<C>&>(*m_componentLists[componentSection<C>()].get());
        }

    private:
        std::vector<std::unique_ptr<IComponentList>> m_componentLists;
    };
}