#pragma once

//////////////
//HEADERS
//////////////
#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Renderer/Light/PointLightParameters.hpp>
#include <Core/World/Component/Component.hpp>
#include <Core/Prefab/Component/TransformComponent.hpp>

namespace ax
{
    struct AXION_CORE_API PointLightComponent : public Component
    {
    public:
        static std::string name(){return "PointLight";}

        PointLightComponent(const Entity& entity);
        ~PointLightComponent();

        void setRadius(float radius) noexcept;
        float getRadius() const noexcept;

        TransformComponent& transform;
    
    private:
        Id m_handle;
        PointLightParameters m_parameters;
    };
}