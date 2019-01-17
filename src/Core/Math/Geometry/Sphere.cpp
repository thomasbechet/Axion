#include <Core/Math/Geometry/Sphere.hpp>

using namespace ax;

Sphere::Sphere(float radius) : m_radius(radius)
{
    
}

float Sphere::getRadius() const noexcept
{
    return m_radius;
}
void Sphere::setRadius(float radius) noexcept
{
    m_radius = radius;
    if(m_radius < 0.0f) m_radius = 0.0f;
}