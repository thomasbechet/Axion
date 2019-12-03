#pragma once

#include <type_traits>

namespace ax
{
    template<typename... types>
    struct archetype;

    template<typename head, typename... tail>
    struct archetype<head, tail...>
    {
        template<typename type>
        static constexpr bool contains()
        {
            return std::is_same<type, head>::value ||
                archetype<tail...>::template contains<type>();
        }
    };

    template<typename head, typename... tail>
    template<typename type>
    constexpr bool archetype<head, tail...>::contains<>() { return false; }

    template<>
    struct archetype<>
    {
        template<typename type>
        static constexpr bool contains() { return false; }
    };
}