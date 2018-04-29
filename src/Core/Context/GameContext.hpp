#pragma once

/////////////////////
//HEADERS
/////////////////////
#include <Core/Export.hpp>
#include <Core/Utility/NonCopyable.hpp>

namespace ax
{
    class AXION_CORE_API GameContext : public NonCopyable
    {
    public:
        void start();
        virtual void onStart() = 0;
        void stop();
        virtual void onStop() = 0;

    private:

    };
}