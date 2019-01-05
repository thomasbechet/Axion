#pragma once

/////////////
//HEADERS
/////////////
#include <Core/Export.hpp>
#include <Core/World/Entity/Entity.hpp>
#include <Core/World/Component/Component.hpp>
#include <Core/Math/Transform.hpp>

#include <string>

namespace ax
{
    struct AXION_CORE_API TransformComponent : public Component, public Transform
    {
        static std::string name(){return "Transform";}

        TransformComponent(
            Vector3f position = Vector3f(0.0f, 0.0f, 0.0f), 
            Quaternionf rotation = Quaternionf(), 
            Vector3f scale = Vector3f(1.0f, 1.0f, 1.0f)
        );

        void attachTo(const Entity& entity) noexcept; 
    };
}