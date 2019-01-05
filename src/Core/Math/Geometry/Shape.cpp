#include <Core/Math/Geometry/Shape.hpp>

using namespace ax;

Shape::Shape()
{

}
Shape::Shape(const std::vector<Vector3f>& points) : m_points(points)
{

}

const std::vector<Vector3f>& Shape::getPoints() const noexcept
{
    return m_points;
}
Vector3f Shape::getPoint(size_t i) const noexcept
{
    return m_points.at(i);
}
void Shape::setPoint(size_t i, const Vector3f& p) noexcept
{
    m_points.at(i) = p;
}

size_t Shape::size() const noexcept
{
    return m_points.size();
}

std::vector<Vertex> Shape::vertices(const Shape& shape, bool smooth) noexcept
{
    return std::vector<Vertex>();
}