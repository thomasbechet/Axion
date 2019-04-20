#include <Core/Math/Geometry/Quad.hpp>

using namespace ax;

Quad::Quad(float x, float y) :
    m_x(x), m_y(y)
{

}   

float Quad::getX() const noexcept
{
    return m_x;
}
void Quad::setX(float x) noexcept
{
    m_x = x;
}

float Quad::getY() const noexcept
{
    return m_y;
}
void Quad::setY(float y) noexcept
{
    m_y = y;
}

std::vector<Vertex> Quad::vertices(
    float x, float y,
    float coordinateFactor
) noexcept
{
    std::vector<Vertex> vertices;

    vertices.reserve(6);

    float midX = x / 2.0f;
    float midY = y / 2.0f;

    //Generate points
    Vertex v0, v1, v2, v3;

    v0.normal = Vector3f::up;
    v0.tangent = Vector3f::right;
    v0.uv = Vector2f(0.0f, coordinateFactor);
    v0.position = Vector3f(-midX, 0.0f, -midY);

    v1.normal = Vector3f::up;
    v1.tangent = Vector3f::right;
    v1.uv = Vector2f(coordinateFactor, coordinateFactor);
    v1.position = Vector3f(midX, 0.0f, -midY);

    v2.normal = Vector3f::up;
    v2.tangent = Vector3f::right;
    v2.uv = Vector2f(coordinateFactor, 0.0f);
    v2.position = Vector3f(midX, 0.0f, midY);

    v3.normal = Vector3f::up;
    v3.tangent = Vector3f::right;
    v3.uv = Vector2f(0.0f, 0.0f);
    v3.position = Vector3f(-midX, 0.0f, midY);

    //Fill mesh
    vertices.emplace_back(v0);
    vertices.emplace_back(v3);
    vertices.emplace_back(v2);
    vertices.emplace_back(v2);
    vertices.emplace_back(v1);
    vertices.emplace_back(v0);

    return vertices;
}