#pragma once

#include <Core/Export.hpp>
#include <Core/Math/Geometry/Vertex.hpp>

#include <vector>

namespace ax
{
    class AXION_CORE_API Quad
    {
    public:
        Quad(float x = 1.0f, float y = 1.0f);

        float getX() const noexcept;
        void setX(float x) noexcept;

        float getY() const noexcept;
        void setY(float y) noexcept;

    public:
        static std::vector<Vertex> vertices(
            float x = 1.0f, float y = 1.0f,
            float coordinateFactor = 1.0f
        ) noexcept;

    protected:
        float m_x;
        float m_y;
    };
}