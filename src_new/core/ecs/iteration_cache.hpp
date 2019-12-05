#pragma once

#include <tuple>
#include <vector>

namespace ax
{
    class iteration_cache_interface
    {
    public:
        virtual ~iteration_cache_interface() = default;
    };

    template<typename... types>
    class iteration_cache : 
        public iteration_cache_interface,
        public std::vector<std::tuple<types...>>
    {};
}