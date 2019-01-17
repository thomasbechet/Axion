#pragma once

//////////////
//HEADERS
//////////////
#include <Core/Export.hpp>

namespace ax
{
    class AXION_CORE_API Sphere
    {
    public:
        Sphere(float radius = 1.0f);

        float getRadius() const noexcept;
        void setRadius(float radius) noexcept;

    protected:
        float m_radius = 1.0f;
    };
}