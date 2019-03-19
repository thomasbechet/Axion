#pragma once

#include <Core/Export.hpp>
#include <Core/GUI/GUIWidget.hpp>

namespace ax
{
    class AXION_CORE_API GUIText : public GUIWidget
    {
    public:
        GUIText(GUILayout& layout);
        ~GUIText();
    };
}