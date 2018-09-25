#pragma once

//////////////
//HEADERS
//////////////
#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/World/Entity/Entity.hpp>
#include <Core/Prefabs/Component/TransformComponent.hpp>

#include <string>

namespace ax
{
    struct AXION_CORE_API CameraComponent : public Component
    {
    public:
        static std::string name(){return "Camera";}
        
        CameraComponent(const Entity& entity);
        ~CameraComponent();

        TransformComponent& transform;

    private:
        Id m_handle;
    };
}