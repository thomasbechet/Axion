#pragma once

////////////////
//HEADERS
////////////////
#include <Core/Export.hpp>
#include <Core/Math/Geometry/Shape.hpp>
#include <Core/Math/Geometry/Sphere.hpp>
#include <Core/Math/Geometry/Vertex.hpp>

namespace ax
{
    class AXION_CORE_API UVSphere : public Shape, public Sphere
    {
    public:
        UVSphere(float radius = 1.0f, unsigned UN = 10, unsigned VN = 10);

        void setRadius(float radius) noexcept;

    public:
        static std::vector<Vertex> vertices(
            float radius = 1.0f, 
            unsigned UN = 30, 
            unsigned UV = 30, 
            bool smooth = true, 
            float coordinateFactor = 1.0f
        ) noexcept; 

    private:
        unsigned m_UN = 10;
        unsigned m_VN = 10;
    };
}