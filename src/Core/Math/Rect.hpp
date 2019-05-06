#pragma once

#include <Core/Export.hpp>

namespace ax
{
    template<typename T>
    class AXION_CORE_API Rect
    {
    public:
        T width = (T)0;
        T height = (T)0;
        T bottom = (T)0;
        T left = (T)0;
    };

    using Rectf = Rect<float>;
    using Rectd = Rect<double>;
    using Recti = Rect<int>;
    using Rectu = Rect<unsigned>;
}