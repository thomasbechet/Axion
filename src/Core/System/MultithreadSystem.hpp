#pragma once

////////////////
//HEADERS
////////////////
#include <Core/Export.hpp>

namespace ax
{
    class AXION_CORE_API MultithreadSystem
    {
    public:
        friend class SystemManager;

    public:
        virtual ~MultithreadSystem(){}

        virtual std::string name(){return "Multithread";}

        virtual void initialize(){}
        virtual void terminate(){}

        virtual void start(){}
        virtual void stop(){}
        virtual void update(){}
    };
}