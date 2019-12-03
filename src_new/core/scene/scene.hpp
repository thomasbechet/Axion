#pragma once

#include <core/utility/non_copyable.hpp>
#include <core/scene/entity.hpp>

namespace ax
{
    class scene : public non_copyable
    {
    public:
        entity create_entity() noexcept;
        void destroy_entity(entity& entity) noexcept;

    private:

    };
}