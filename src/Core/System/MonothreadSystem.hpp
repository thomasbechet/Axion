#pragma once

/////////////////
//HEADERS
/////////////////
#include <Core/Export.hpp>
#include <Core/Entity/ComponentIterator.hpp>

namespace ax
{
    class AXION_CORE_API MonothreadSystem
    {
    public:
        friend class SystemManager;

    public:
        virtual ~MonothreadSystem(){}

        //virtual std::string name(){return "Monothread";}

        virtual void initialize(){}
        virtual void terminate(){}

        virtual void start(){}
        virtual void stop(){}
        virtual void update(){}
    };
}