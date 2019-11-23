#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Json.hpp>
#include <Core/Utility/NonCopyable.hpp>

namespace ax
{
    struct AXION_CORE_API ComponentHandle
    {
        unsigned section : 8;
        unsigned offset : 24;
    };

    class AXION_CORE_API Component : public NonCopyable
    {
    public:
        virtual Json json() const noexcept;
    };
}