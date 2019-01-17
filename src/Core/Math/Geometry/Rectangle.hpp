#pragma once

//////////////
//HEADERS
//////////////
#include <Core/Export.hpp>
#include <Core/Math/Geometry/Vertex.hpp>

#include <vector>

namespace ax
{
    class AXION_CORE_API Rectangle
    {
    public:
        Rectangle(
            float xMin = -0.5f, float xMax = 0.5f,
            float yMin = -0.5f, float yMax = 0.5f,
            float zMin = -0.5f, float zMax = 0.5f
        );

        float getMinX() const noexcept;
        void setMinX(float x) noexcept;

        float getMaxX() const noexcept;
        void setMaxX(float x) noexcept;

        float getMinY() const noexcept;
        void setMinY(float y) noexcept;

        float getMaxY() const noexcept;
        void setMaxY(float y) noexcept;

        float getMinZ() const noexcept;
        void setMinZ(float z) noexcept;

        float getMaxZ() const noexcept;
        void setMaxZ(float z) noexcept;

    public:
        static std::vector<Vertex> vertices(
            float xMin, float xMax, 
            float yMin, float yMax, 
            float zMin, float zMax, 
            bool smooth = false, 
            float coordinateFactor = 1.0f
        ) noexcept;

    protected:
        float m_xMin;
        float m_xMax;
        float m_yMin;
        float m_yMax;
        float m_zMin;
        float m_zMax;
    };
}