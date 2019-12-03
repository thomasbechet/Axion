#pragma once

#include <core/utility/non_copyable.hpp>
#include <core/utility/types.hpp>

namespace ax
{
    struct component_id
    {
        unsigned archetype_id : 10;
        unsigned id : 22;
    };

    template<typename T>
    class component_reference
    {
    public:
        component_reference() noexcept;

        void invalidate() noexcept;
        T* operator*() const noexcept;

    private:
        T* pointer = nullptr;
        ax::id id;
    };
}