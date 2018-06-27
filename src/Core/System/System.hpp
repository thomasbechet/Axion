#pragma once

/////////////////
//HEADERS
/////////////////
#include <Core/Export.hpp>
#include <Core/Utility/NonCopyable.hpp>

namespace ax
{
    class AXION_CORE_API System : public NonCopyable
    {
    public:
        friend class SystemManager;

    public:
        virtual ~System(){}

        virtual void onInitialize(){}
        virtual void onTerminate(){}
        virtual void onStart(){}
        virtual void onStop(){}
        virtual void onTick(){}
        virtual void onActive(){}
        virtual void onDisable(){}

    public:
        void active() noexcept;
        void disable() noexcept;
        bool isActive() const noexcept;
    
    private:
        bool m_active = true;
    };
}