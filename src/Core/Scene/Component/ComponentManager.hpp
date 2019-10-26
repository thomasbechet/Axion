#pragma once 

#include <Core/Export.hpp>
#include <Core/Utility/NonCopyable.hpp>
#include <Core/Scene/Component/Component.hpp>
#include <Core/Scene/Component/ComponentList.hpp>

#include <vector>
#include <memory>
#include <unordered_map>
#include <typeindex>

namespace ax
{
    class AXION_CORE_API ComponentManager : public NonCopyable
    {
    private:
        std::unordered_map<std::type_index, size_t> m_indexes;

        template<typename C>
        size_t getSection() noexcept;

    public:
        template<typename C>
        size_t componentSection() noexcept;

        template<typename C, typename... Args>
        ComponentHandle create(const Entity& entity, Args&&... args) noexcept;

        void destroy(ComponentHandle handle) noexcept;

        template<typename C>
        C& get(ComponentHandle handle) noexcept;

        template<typename C>
        ComponentList<C>& getList() noexcept;

    private:
        std::vector<std::unique_ptr<IComponentList>> m_componentLists;
    };
}