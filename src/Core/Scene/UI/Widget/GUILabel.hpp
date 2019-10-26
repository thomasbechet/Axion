#pragma once

#include <Core/Export.hpp>
#include <Core/GUI/GUIWidget.hpp>

namespace ax
{
    class AXION_CORE_API GUILabel : public GUIWidget
    {
    public:
        GUILabel(GUILayout& layout);
        ~GUILabel();
    };
}