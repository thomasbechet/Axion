#include <Core/Math/Geometry/Sphere.hpp>

using namespace ax;

Sphere::Sphere(float radius) : m_radius(radius)
{
    
}

float Sphere::getRadius() const noexcept
{
    return m_radius;
}