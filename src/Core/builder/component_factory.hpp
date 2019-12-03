#pragma once

#include <core/export.hpp>
#include <core/scene/entity/entity.hpp>
#include <core/utility/json.hpp>

namespace ax
{
    class AXION_CORE_API component_factory_interface
    {
    public:
        virtual ~component_factory_interface() = default;
        virtual void add(entity& entity, const json& json) noexcept = 0;
        virtual void remove(entity& entity) noexcept = 0;
        virtual const std::vector<std::string>& requirements() const noexcept = 0;
    };

    template<typename type>
    class AXION_CORE_API component_factory : public component_factory_interface
    {
    public:
        void add(entity& entity, const json& json) noexcept override;
        void remove(Entity& entity) noexcept override;
        const std::vector<std::string>& requirements() const noexcept;
    };
}