#pragma once

#include <core/export.hpp>
#include <core/utility/non_copyable.hpp>

namespace ax
{
    class AXION_CORE_API module : public non_copyable
    {
    public:
        virtual void initialize() noexcept = 0;
        virtual void terminate() noexcept = 0;
    };
}