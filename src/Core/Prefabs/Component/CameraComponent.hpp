#pragma once

//////////////
//HEADERS
//////////////
#include <Core/Export.hpp>

namespace ax
{
    class AXION_CORE_API CameraComponent : public Component
    {
    public:
        static std::string name(){return "Camera";}
        void load(const Entity& e) noexcept;
        void unload() noexcept;
    };
}