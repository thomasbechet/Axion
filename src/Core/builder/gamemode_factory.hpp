#pragma once

#include <core/export.hpp>
#include <core/scene/entity/entity.hpp>
#include <core/utility/json.hpp>

namespace ax
{
    class AXION_CORE_API gamemode_factory_interface
    {
    public:
        virtual ~gamemode_factory() = default;
        virtual void set() noexcept = 0;
    };

    template<typename type>
    class AXION_CORE_API gamemode_factory : public gamemode_factory_interface
    {
    public:
        void set() noexcept override;
    };
}