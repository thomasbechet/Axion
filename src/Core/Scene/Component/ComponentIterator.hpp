#pragma once

#include <Core/Export.hpp>
#include <Core/Scene/Component/ComponentList.ipp>

namespace ax
{
    template<typename C>
    class AXION_CORE_API ComponentIterator
    {
    public:
        friend class ComponentList<C>;

    public:
        ComponentIterator(const ComponentList<C>& list, size_t start, size_t end);

        bool next() noexcept;
        C* operator->() noexcept;

    private:
        size_t m_index;
        size_t m_start;
        size_t m_end;
        C* m_current = nullptr;
        const ComponentList<C>& m_list;
    };
}