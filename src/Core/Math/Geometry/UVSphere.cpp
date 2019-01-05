#include <Core/Math/Geometry/UVSphere.hpp>

using namespace ax;

UVSphere::UVSphere(float radius, unsigned UN, unsigned VN) : Sphere(radius)
{

}

void UVSphere::setRadius(float radius) noexcept
{
    m_radius = radius;
}

std::vector<Vertex> UVSphere::vertices(float radius, unsigned UN, unsigned VN, bool smooth) noexcept
{
    std::vector<Vertex> vertices;
    std::vector<size_t> indices;
    std::vector<Vector3f> points;

    points.reserve(UN * VN);

    vertices.reserve(UN * VN * 6);

    for(unsigned i = 0; i < UN, i++)
    {
        for(unsigned j = 0; j < UN; j++)
        {
            
        }
    }

    Vertex v;

    v.position = Vector3f(0.0f, 0.0f, 0.0f);
    v.normal = Vector3f(0.0f, 1.0f, 0.0f);
    v.tangent = Vector3f(1.0f, 0.0f, 0.0f);
    v.color = Vector3f(1.0f, 1.0f, 1.0f);
    vertices.push_back(v);

    v.position = Vector3f(0.0f, 0.0f, -1.0f);
    v.normal = Vector3f(0.0f, 1.0f, 0.0f);
    v.tangent = Vector3f(1.0f, 0.0f, 0.0f);
    v.color = Vector3f(1.0f, 1.0f, 1.0f);
    vertices.push_back(v);

    v.position = Vector3f(1.0f, 0.0f, 1.0f);
    v.normal = Vector3f(0.0f, 1.0f, 0.0f);
    v.tangent = Vector3f(1.0f, 0.0f, 0.0f);
    v.color = Vector3f(1.0f, 1.0f, 1.0f);
    vertices.push_back(v);

    return vertices;
}