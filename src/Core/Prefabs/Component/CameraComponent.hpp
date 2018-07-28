#pragma once

//////////////
//HEADERS
//////////////
#include <Core/Export.hpp>

namespace ax
{
    struct AXION_CORE_API CameraComponent : public Component
    {
        static std::string name(){return "Camera";}
        
    };
}