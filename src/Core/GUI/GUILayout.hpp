#pragma once

#include <Core/Export.hpp>
#include <Core/GUI/Widget/GUIButton.hpp>
#include <Core/GUI/Widget/GUILabel.hpp>

#include <vector>
#include <memory>

namespace ax
{
    class AXION_CORE_API GUILayout
    {
    public:
        GUILayout();
        virtual ~GUILayout();

        void update() noexcept;

        bool hasFocus() noexcept;
        void focus() noexcept;
        void unfocus() noexcept;

    public:
        virtual void onStart(){}
        virtual void onStop(){}
        virtual void onUpdate(){}

    protected:
        template<typename T>
        T& add() noexcept
        {

        }
        void remove(GUIWidget& widget) noexcept;

    private:
        

        std::vector<std::unique_ptr<GUIButton>> m_buttons;
        std::vector<std::unique_ptr<GUILabel>> m_labels;
        bool m_hasFocus = false;
        Id m_handle;
    };
}