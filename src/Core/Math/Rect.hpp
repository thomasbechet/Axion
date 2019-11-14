#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Json.hpp>

namespace ax
{
    template<typename T>
    class AXION_CORE_API Rect
    {
    public:
        Rect() = default;

        Json json() const noexcept
        {
            return {width, height, bottom, left};
        }
        static Rect<T> parse(const Json& json) noexcept
        {
            Rect<T> rect;

            try
			{
                if(json.is_array())
                {
                    std::vector<T> values = json.get<std::vector<T>>();
                    if(values.size() == 4)
                    {
                        rect.width = values.at(0);
                        rect.height = values.at(1);
                        rect.bottom = values.at(2);
                        rect.left = values.at(3);
                    }
                }
			}
			catch(...) {}

            return rect;
        }

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