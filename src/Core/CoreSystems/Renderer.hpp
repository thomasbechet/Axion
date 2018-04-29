#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/Context/GameContext.hpp>

namespace ax
{
    class AXION_CORE_API Renderer
    {
    public:
        using id = unsigned;

    public:
        virtual void init(GameContext& context);
        virtual void terminate(GameContext& context);
    };
}