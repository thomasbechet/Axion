#pragma once

#include <Core/Export.hpp>
#include <Core/Math/Transform2D.hpp>

namespace ax
{
    class AXION_CORE_API UIComponent
    {
    public:
        UIComponent() = default;
        UIComponent(UIComponent& component);
        ~UIComponent() = default;

        void setPosition(float x, float y) noexcept;
        Vector2f getPosition() const noexcept;
        void setRotation(float rotation) noexcept;
        float getRotation() const noexcept;
        void setScale(float x, float y) noexcept;
        Vector2f getScale() const noexcept;

        void attachTo(UIComponent& component) noexcept;
        void detach() noexcept;
        bool isAttached() const noexcept;

    protected:
        UIComponent& m_parent;
        Transform2D m_transform;
    };
}