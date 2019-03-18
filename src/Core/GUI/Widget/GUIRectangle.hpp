#pragma once

#include <Core/Export.hpp>
#include <Core/GUI/Widget/GUIWidget.hpp>

#include <functional>

namespace ax
{
    class AXION_CORE_API GUIRectangle : public GUIWidget
    {
    public:
        void onClicked(std::function<void()> function) noexcept;
        void onPressed(std::function<void()> function) noexcept;
        void onReleased(std::function<void()> function) noexcept;
        void onEntered(std::function<void()> function) noexcept;
        void onLeaved(std::function<void()> function) noexcept;

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