#pragma once

#include <Core/Export.hpp>
#include <Core/Scene/Entity/Entity.hpp>
#include <Core/Utility/Json.hpp>

namespace ax
{
    class AXION_CORE_API IGameModeFactory
    {
    public:
        virtual ~IGameModeFactory() = default;
        virtual void set() noexcept = 0;
    };

    template<typename C>
    class AXION_CORE_API GameModeFactory : public IGameModeFactory
    {
    public:
        void set() noexcept override;
    };
}