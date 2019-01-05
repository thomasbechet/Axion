#pragma once

//////////////
//HEADERS
//////////////
#include <Core/Export.hpp>
#include <Core/Math/Vector.hpp>
#include <Core/Math/Geometry/Vertex.hpp>

#include <vector>

namespace ax
{
    class AXION_CORE_API Shape
    {
    public:
        Shape();
        Shape(const std::vector<Vector3f>& points);

        const std::vector<Vector3f>& getPoints() const noexcept;
        
        Vector3f getPoint(size_t i) const noexcept;
        void setPoint(size_t i, const Vector3f& p) noexcept;

        size_t size() const noexcept;

    public:
        static std::vector<Vertex> vertices(const Shape& shape, bool smooth = false) noexcept; 

    protected:
        std::vector<Vector3f> m_points;
    };
}