#pragma once

#include <Core/Export.hpp>
#include <Core/GUI/Widget/GUIButton.hpp>
#include <Core/GUI/Widget/GUIText.hpp>

namespace ax
{
    class AXION_CORE_API GUILayout
    {
    public:
        GUILayout();
        virtual ~GUILayout();

    public:
        virtual void onStart(){}
        virtual void onStop(){}
        virtual void onUpdate(){}

    protected:
        GUIButton& addButton() noexcept;
        void removeButton(GUIButton& button) noexcept;
        GUIText& addText() noexcept;
        void removeText(GUIText& text) noexcept;

    private:
        Id m_handle;
    };
}