#pragma once

#include <Core/Export.hpp>
#include <Core/GUI/GUIWidget.hpp>

#include <functional>

namespace ax
{
    class AXION_CORE_API GUIRectangle : public GUIWidget
    {
    public:
        GUIRectangle(GUILayout& layout);
        virtual ~GUIRectangle() = default;

        void onClicked(std::function<void()> function) noexcept;
        void onPressed(std::function<void()> function) noexcept;
        void onReleased(std::function<void()> function) noexcept;
        void onEntered(std::function<void()> function) noexcept;
        void onLeaved(std::function<void()> function) noexcept;

        void callOnClicked() const noexcept;
        void callOnPressed() const noexcept;
        void callOnReleased() const noexcept;
        void callOnEntered() const noexcept;
        void callOnLeaved() const noexcept;

        void setSize(unsigned x, unsigned y) noexcept;
        void setSize(Vector2u size) noexcept;
        Vector2u getSize() const noexcept;

        bool intersect(Vector2i point) const noexcept;

    protected:
        Vector2u m_size;
    
        std::function<void()> m_onClicked;
        std::function<void()> m_onPressed;
        std::function<void()> m_onReleased;
        std::function<void()> m_onEntered;
        std::function<void()> m_onLeaved;
    };
}