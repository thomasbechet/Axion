#pragma once

/////////////////
//HEADERS
/////////////////
#include <Core/Export.hpp>
#include <Core/Entity/ComponentIterator.hpp>

namespace ax
{
    class AXION_CORE_API System
    {
    public:
        friend class SystemManager;

    public:
        virtual ~System(){}

        virtual void initialize(){}
        virtual void terminate(){}

        virtual void start(){}
        virtual void stop(){}
        virtual void tick(){}

    public:
        void active() noexcept;
        void disable() noexcept;
        bool isActive() const noexcept;
    
    private:
        bool m_active = true;
    };
}