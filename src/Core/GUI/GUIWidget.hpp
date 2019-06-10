#pragma once

#include <Core/Export.hpp>
#include <Core/Math/Transform2D.hpp>
#include <Core/Utility/NonCopyable.hpp>
#include <Core/Utility/Types.hpp>

namespace ax
{
    class GUILayout;

    class AXION_CORE_API GUIWidget : public NonCopyable
    {
    public:
        friend class GUILayout;
        GUIWidget(GUILayout& layout);
        virtual GUIWidget() = 0;

        void setPosition(int x, int y) noexcept;
        virtual void setPosition(const Vector2i& position) noexcept;
        Vector2i getPosition() const noexcept;
        virtual void setRotation(float rotation) noexcept;
        float getRotation() const noexcept;
        void setScale(float x, float y) noexcept;
        virtual void setScale(const Vector2f& scale) noexcept;
        Vector2f getScale() const noexcept;

        void attachTo(GUIWidget& component) noexcept;
        void detach() noexcept;
        
        bool isAttached() const noexcept;
        GUIWidget& getParent() const noexcept;
        bool hasChild() const noexcept;
        GUIWidget& getFirstChild() const noexcept;
        bool hasSibling() const noexcept;
        GUIWidget& getNextSibling() const noexcept;

        void setSize(unsigned width, unsigned height) noexcept;
        virtual void setSize(const Vector2u& size) noexcept;
        Vector2u getSize() const noexcept;
        Recti getLocalBounds() const noexcept;
        Recti getGlobalBounds() const noexcept;

        GUILayout& getLayout() const noexcept;
        Id getID() const noexcept;

    protected:
        Transform2D* transformData() const noexcept;

        virtual void update() noexcept = 0;

    private:
        GUIWidget* m_parent = nullptr;
        GUIWidget* m_nextSibling = nullptr;
        GUIWidget* m_firstChild = nullptr;
        Transform2D m_transform;

        Vector2u m_size;
        Recti m_localBounds;
        Recti m_globalBounds;

        GUILayout& m_layout;
        Id id;
    };
}