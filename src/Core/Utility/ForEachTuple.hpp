#pragma once

#include <Core/Export.hpp>

#include <tuple>

namespace ax
{
    template<typename Type, typename F, int index, int max>
    struct AXION_CORE_API foreach_tuple_impl
    {
        void operator()(Type& t, F f)
        {
            f(std::get<index>(t));
            foreach_tuple_impl<Type, F, index + 1, max>()(t, f);
        }
    };
    template<typename Type, typename F, int max>
    struct AXION_CORE_API foreach_tuple_impl<Type, F, max, max>
    {
        void operator()(Type& t, F f)
        {
            f(std::get<max>(t));
        }
    };

    template<typename Type, typename F>
    static void AXION_CORE_API foreach_tuple(Type& t, F f)
    {
        foreach_tuple_impl<Type, F, 0, std::tuple_size<Type>::value - 1>()(t, f);
    }
}

