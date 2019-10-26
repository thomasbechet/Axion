#pragma once

#include <Core/Export.hpp>

namespace ax
{
    struct AXION_CORE_API ComponentHandle
    {
        unsigned section : 8;
        unsigned offset : 24;
    };

    struct AXION_CORE_API Component
    {
    public:
        
    };
}