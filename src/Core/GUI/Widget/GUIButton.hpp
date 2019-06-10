#pragma once

#include <Core/Export.hpp>
#include <Core/GUI/GUIRectangle.hpp>

#include <functional>

namespace ax
{
    class AXION_CORE_API GUIButton : public GUIRectangle
    {
    public:
        friend class GUILayout;

    private:
        GUIButton(GUILayout& layout);
        ~GUIButton();
    };
}