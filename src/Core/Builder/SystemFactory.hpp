#pragma once

#include <Core/Export.hpp>

namespace ax
{
    class AXION_CORE_API ISystemFactory
    {
    public:
        virtual ~ISystemFactory() = default;
        virtual void add() noexcept = 0;
        virtual void remove() noexcept = 0;
    };

    template<typename C>
    class AXION_CORE_API SystemFactory : public ISystemFactory
    {
    public:
        void add() noexcept override;
        void remove() noexcept override;
    };
}