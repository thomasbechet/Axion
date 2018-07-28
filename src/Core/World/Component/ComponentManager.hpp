#pragma once 

/////////////////
//HEADERS
/////////////////
#include <vector>
#include <memory>
#include <Core/Export.hpp>
#include <Core/Utility/NonCopyable.hpp>
#include <Core/World/Component/Component.hpp>
#include <Core/World/Component/ComponentList.hpp>

#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>

namespace ax
{
    class AXION_CORE_API ComponentManager : public NonCopyable
    {
    private:
        std::unordered_map<std::type_index, size_t> m_indexes;

        template<typename C>
        size_t getSection() noexcept
        {
            std::type_index index = std::type_index(typeid(C));

            if(m_indexes.find(index) != m_indexes.end())
                return m_indexes.at(index);

            m_componentLists.emplace_back(std::make_unique<ComponentList<C>>());
            m_indexes[index] = m_componentLists.size() - 1;

            return m_componentLists.size() - 1;
        }

    public:
        template<typename C>
        size_t componentSection() noexcept
        {
            static size_t section = getSection<C>();
            return section;
        }

        template<typename C, typename... Args>
        ComponentHandle create(Args&&... args) noexcept
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
        C& get(ComponentHandle handle) noexcept
        {
            return static_cast<ComponentList<C>&>(*m_componentLists[handle.section].get()).get(handle.offset);
        }

        template<typename C>
        ComponentList<C>& getList() noexcept
        {
            return static_cast<ComponentList<C>&>(*m_componentLists[componentSection<C>()].get());
        }

    private:
        std::vector<std::unique_ptr<IComponentList>> m_componentLists;
    };
}