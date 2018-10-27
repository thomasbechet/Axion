#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>

namespace ax
{
    enum AXION_CORE_API RenderMode
    {
        Default,
        
        ForwardShading,
        ForwardPlusShading,
        DeferredShading,
        TiledDeferredShading,

        Wireframe,
        Debug0,
        Debug1,
        Debug2,
        Debug3,
        Debug4,

        Custom0,
        Custom1,
        Custom2,
        Custom3,
        Custom4
    };  
}