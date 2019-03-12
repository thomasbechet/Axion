#include <Core/Math/Geometry/UVSphere.hpp>

#include <Core/Math/Math.hpp>

using namespace ax;

UVSphere::UVSphere(float radius, unsigned UN, unsigned VN) : Sphere(radius)
{
    m_UN = UN;
    m_VN = VN;
}

void UVSphere::setSliceCount(unsigned slice) noexcept
{
    m_UN = slice;
    if(m_UN < 1) m_UN = 1;
}
void UVSphere::setStackCount(unsigned stack) noexcept
{
    m_VN = stack;
    if(m_VN < 1) m_VN = 1;
}

std::vector<Vertex> UVSphere::vertices(float radius, unsigned UN, unsigned VN, bool smooth, float coordinateFactor) noexcept
{
    std::vector<Vertex> vertices;

    vertices.reserve(((VN - 2) * UN * 6) + (2 * UN * 3));

    for(unsigned v = 0; v < VN; v++)
    {
        float advanceV1 = ((float)(v) / (float)VN);
        float advanceV2 = ((float)(v + 1) / (float)VN);

        float theta1 = advanceV1 * PI;
        float cosTheta1 = std::cos(theta1);
        float sinTheta1 = std::sin(theta1);
        float theta2 = advanceV2 * PI;
        float cosTheta2 = std::cos(theta2);
        float sinTheta2 = std::sin(theta2);

        for(unsigned u = 0; u < UN; u++)
        {
            float advanceU1 = ((float)(u) / (float)UN);
            float advanceU2 = ((float)(u + 1) / (float)UN);

            float phi1 = advanceU1 * 2.0f * PI;
            float cosPhi1 = std::cos(phi1);
            float sinPhi1 = std::sin(phi1);
            float phi2 = advanceU2 * 2.0f * PI;
            float cosPhi2 = std::cos(phi2);
            float sinPhi2 = std::sin(phi2);

            //Generate quad points
            Vector3f p1;
            p1.x = cosPhi1 * sinTheta1;
            p1.y = cosTheta1;
            p1.z = sinPhi1 * sinTheta1;
            Vector3f p2;
            p2.x = cosPhi2 * sinTheta1;
            p2.y = cosTheta1;
            p2.z = sinPhi2 * sinTheta1;
            Vector3f p3;
            p3.x = cosPhi2 * sinTheta2;
            p3.y = cosTheta2;
            p3.z = sinPhi2 * sinTheta2;
            Vector3f p4;
            p4.x = cosPhi1 * sinTheta2;
            p4.y = cosTheta2;
            p4.z = sinPhi1 * sinTheta2;

            //Generate vertices
            Vertex v1, v2, v3, v4;
            v1.position = p1 * radius;
            v2.position = p2 * radius;
            v3.position = p3 * radius;
            v4.position = p4 * radius;
            //Normals and tangent
            if(smooth)
            {
                v1.normal = p1;
                v1.tangent = Vector3f::cross(Vector3f::up, v1.normal);
                v2.normal = p2;
                v2.tangent = Vector3f::cross(Vector3f::up, v2.normal);
                v3.normal = p3;
                v3.tangent = Vector3f::cross(Vector3f::up, v3.normal);
                v4.normal = p4;
                v4.tangent = Vector3f::cross(Vector3f::up, v4.normal);

                //Need to patch bottom normals (p1 and p2 are the same)
                if(v == 0)
                {
                    v1.tangent = Vector3f::right;
                    v2.tangent = Vector3f::right;
                }
            }
            else
            {
                Vector3f tangent = p4 - p3;
                Vector3f dy = p4 - p1;
                Vector3f dx = p3 - p4;

                //Need to patch bottom normals (p3 and p4 are the same)
                if(v + 1 == VN)
                    dx = p2 - p1;

                Vector3f normal = Vector3f::cross(dx, dy);
                v1.normal = normal;
                v1.tangent = tangent;
                v2.normal = normal;
                v2.tangent = tangent;
                v3.normal = normal;
                v3.tangent = tangent;
                v4.normal = normal;
                v4.tangent = tangent;
            }
            //UVs
            v1.uv = Vector2f(
                1.0f - advanceU1,
                1.0f - advanceV1
            ) * coordinateFactor;
            v2.uv = Vector2f(
                1.0f - advanceU2,
                1.0f - advanceV1
            ) * coordinateFactor;
            v3.uv = Vector2f(
                1.0f - advanceU2,
                1.0f - advanceV2
            ) * coordinateFactor;
            v4.uv = Vector2f(
                1.0f - advanceU1,
                1.0f - advanceV2
            ) * coordinateFactor;

            /*v1.uv = Vector2f(
                advanceU1,
                1.0f - advanceV1
            ) * coordinateFactor;
            v2.uv = Vector2f(
                advanceU2,
                1.0f - advanceV1
            ) * coordinateFactor;
            v3.uv = Vector2f(
                advanceU2,
                1.0f - advanceV2
            ) * coordinateFactor;
            v4.uv = Vector2f(
                advanceU1,
                1.0f - advanceV2
            ) * coordinateFactor;*/

            //Filling mesh with vertices
            if(v == 0) //Top
            {
                vertices.emplace_back(v1);
                vertices.emplace_back(v3);
                vertices.emplace_back(v4);
            }
            else if(v + 1 == VN) //Bottom
            {
                vertices.emplace_back(v2);
                vertices.emplace_back(v3);
                vertices.emplace_back(v1);
            }
            else
            {
                vertices.emplace_back(v4);
                vertices.emplace_back(v1);
                vertices.emplace_back(v2);

                vertices.emplace_back(v4);
                vertices.emplace_back(v2);
                vertices.emplace_back(v3);
            }
        }
    }

    return vertices;
}