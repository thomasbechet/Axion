#pragma once

#include <core/utility/non_copyable.hpp>

namespace ax
{
    class system : public non_copyable
    {
    public:
        virtual void on_start() noexcept {};
        virtual void on_stop() noexcept {};
        virtual void on_update() noexcept {};
    };
}