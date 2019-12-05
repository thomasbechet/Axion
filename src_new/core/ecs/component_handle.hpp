#pragma once

namespace ax
{
    struct component_handle
    {
        unsigned section : 12; 
        unsigned id : 20;
    };
}