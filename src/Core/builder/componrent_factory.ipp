#pragma once

#include <core/builder/component_factory.hpp>

namespace ax
{
    template<typename type>
    void component_factory<type>::add(entity& entity, const Json& json) noexcept
    {
        entity.add_component<type>(json);
    }
    template<typename type>
    void component_factory<type>::remove(entity& entity) noexcept
    {
        entity.remove_component<type>();
    }
    template<typename type>
    const std::vector<std::string>& component_factory<type>::requirements() const noexcept
    {
        return type::requirements;
    }
}