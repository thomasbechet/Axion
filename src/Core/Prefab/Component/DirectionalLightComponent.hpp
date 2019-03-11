#pragma once

//////////////
//HEADERS
//////////////
#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Renderer/Light/DirectionalLightParameters.hpp>
#include <Core/World/Component/Component.hpp>
#include <Core/Prefab/Component/TransformComponent.hpp>

namespace ax
{
    struct AXION_CORE_API DirectionalLightComponent : public Component
    {
    public:
        static const std::string name;

        DirectionalLightComponent(const Entity& entity);
        ~DirectionalLightComponent();

        TransformComponent& transform;
    
    private:
        Id m_handle;
        DirectionalLightParameters m_parameters;
    };
}