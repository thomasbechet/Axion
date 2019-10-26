#pragma once

#include <Core/Export.hpp>
#include <Core/Scene/Entity/Entity.ipp>
#include <Core/Scene/Component/Component.hpp>
#include <Core/Math/Transform.hpp>
#include <Core/Utility/Json.hpp>

#include <string>

namespace ax
{
    struct AXION_CORE_API TransformComponent : public Component, public Transform
    {
        static const std::string type;
        //static inline const std::string type = "Transform";

        TransformComponent(const Entity& entity, const Json& json);
        TransformComponent(
            const Entity& entity,
            Vector3f position = Vector3f(0.0f, 0.0f, 0.0f), 
            Quaternionf rotation = Quaternionf(), 
            Vector3f scale = Vector3f(1.0f, 1.0f, 1.0f)
        );

        void attachTo(const Entity& entity) noexcept; 
    };
}