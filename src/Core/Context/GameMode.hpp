#pragma once

//////////////////
//HEADERS
//////////////////
#include <Core/Export.hpp>
#include <Core/Utility/NonCopyable.hpp>

namespace ax
{
    class AXION_CORE_API GameMode : public NonCopyable
    {
    public:
        virtual ~GameMode();

        virtual void onStart(){}
        virtual void onStop(){}
        virtual void onPause(){}
        virtual void onResume(){}
    };
}