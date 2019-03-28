#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/NonCopyable.hpp>

namespace ax
{
    struct AXION_CORE_API ComponentHandle
    {
        unsigned section : 8;
        unsigned offset : 24;
    };

    /*template<typename C>
    class AXION_CORE_API ComponentReference
    {
    public:
        C* operator->()
        {
            return &ax::Game::components().getComponent<C>(m_handle);
        }

    private:
        ComponentHandle m_handle;
    };*/

    struct AXION_CORE_API Component
    {
    public:
        
    };
}