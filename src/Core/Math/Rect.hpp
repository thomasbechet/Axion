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
        Rect(const Json& json)
        {
            try
			{
				std::vector<T> values = json.get<std::vector<T>>();
                if(values.size() >= 4)
                {
                    width = values.at(0);
                    height = values.at(1);
                    bottom = values.at(2);
                    left = values.at(3);
                }
			}
			catch(...) {}
        }

        Json json() const noexcept
        {
            return {width, height, bottom, left};
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