#pragma once

#include <Core/Export.hpp>
#include <Core/Math/Transform2D.hpp>
#include <Core/GUI/GUILayout.hpp>

namespace ax
{
    class AXION_CORE_API GUIWidget
    {
    public:
        GUIWidget(GUILayout& layout);

        void setPosition(int x, int y) noexcept;
        void setPosition(Vector2i position) noexcept;
        Vector2i getPosition() const noexcept;
        void setRotation(float rotation) noexcept;
        float getRotation() const noexcept;
        void setScale(float x, float y) noexcept;
        void setScale(Vector2f scale) noexcept;
        Vector2f getScale() const noexcept;

        void attachTo(GUIWidget& component) noexcept;
        void detach() noexcept;
        bool isAttached() const noexcept;

    protected:
        GUIWidget* m_parent = nullptr;
        GUIWidget* m_nextSibling = nullptr;
        GUIWidget* m_firstChild = nullptr;
        Transform2D m_transform;
    };
}