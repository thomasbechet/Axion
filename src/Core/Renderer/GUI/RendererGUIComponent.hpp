#pragma once

#include <Core/Export.hpp>
#include <Core/Math/Transform2D.hpp>
#include <Core/Utility/Color.hpp>

namespace ax
{
    class AXION_CORE_API RendererGUIComponent
    {
    public:
        virtual void setTransform(Transform2D* transform) = 0;
        virtual void setVisible(bool toggle) = 0;
        virtual void setTransparency(float transparency) = 0;
        virtual void setColor(Color3 color) = 0;
        virtual void setDepth(unsigned depth) = 0;
    };
}