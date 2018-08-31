#pragma once

/////////////
//HEADERS
/////////////
#include <Core/Export.hpp>

#include <string>

namespace ax
{
    struct AXION_CORE_API Shader
    {
        std::string vertex;
        std::string fragment;
        
        Id handle;
    };
}