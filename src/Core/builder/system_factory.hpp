#pragma once

#include <core/export.hpp>

namespace ax
{
    class AXION_CORE_API system_factory_interface
    {
    public:
        virtual ~system_factory_interface() = default;
        virtual void add() noexcept = 0;
        virtual void remove() noexcept = 0;
    };

    template<typename type>
    class AXION_CORE_API system_factory : public system_factory_interface
    {
    public:
        void add() noexcept override;
        void remove() noexcept override;
    };
}