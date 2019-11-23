#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Scene/Entity/Entity.hpp>
#include <Core/Content/Component/TransformComponent.hpp>
#include <Core/Renderer/Scene/RendererCamera.hpp>
#include <Core/Renderer/GUI/RendererGUIViewport.hpp>

namespace ax
{
    class AXION_CORE_API CameraComponent : public Component
    {
    public:
        COMPONENT_IDENTIFIER("camera")
        COMPONENT_REQUIREMENTS(TransformComponent) 
          
        CameraComponent(Entity& entity, const Json& json);
        CameraComponent(Entity& entity);
        ~CameraComponent();

        void bindDefaultViewport() noexcept;
        void bindViewport(RendererGUIViewportHandle viewport) noexcept;

        void setFov(float fov) noexcept;
        float getFov() const noexcept;
        void setFarPlane(float far) noexcept;
        float getFarPlane() const noexcept;
        void setNearPlane(float near) noexcept;
        float getNearPlane() const noexcept;

        TransformComponent& transform;

    private:
        void updateRendererParameters() noexcept;
        
        RendererCameraHandle m_handle;
        RendererCameraParameters m_parameters;
    };
}