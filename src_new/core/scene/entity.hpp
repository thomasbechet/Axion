#pragma once

#include <core/utility/types.hpp>

#include <memory>

namespace ax
{
    class entity
    {
    public:
        entity()

    public:
        bool is_valid() const noexcept;
        bool is_activated() const noexcept;
        id get_id() const noexcept;

    private:

    };
}