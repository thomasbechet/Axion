#include <Core/Math/Transform.hpp>

using namespace ax;

const Vector3f& Transform::getTranslation() const noexcept
{
    return m_translation;
}
void Transform::setTranslation(const Vector3f& translation) noexcept
{
    m_translation = translation;
    m_computeRequest = true;
}
void Transform::setTranslation(float x, float y, float z) noexcept
{
    m_translation.x = x;
    m_translation.y = y;
    m_translation.z = z;
    m_computeRequest = true;
}
void Transform::translate(const Vector3f& translation) noexcept
{
    m_translation += translation;
    m_computeRequest = true;
}
void Transform::translate(float x, float y, float z) noexcept
{
    m_translation.x += x;
    m_translation.y += y;
    m_translation.z += z;
    m_computeRequest = true;
}

const Quaternionf& Transform::getRotation() const noexcept
{
    return m_rotation;
}
void Transform::setRotation(const Quaternionf& rotation) noexcept
{
    m_rotation = rotation;
    m_computeRequest = true;
}

const Vector3f& Transform::getScale() const noexcept
{
    return m_scale;
}
void Transform::setScale(const Vector3f& scale) noexcept
{
    m_scale = scale;
    m_computeRequest = true;
}

Matrix4f Transform::matrix() noexcept
{
    if(m_computeRequest)
    {
        computeMatrix();
    }

    return m_transform;
}

void Transform::computeMatrix() noexcept
{
    m_transform = Matrix4f::scale(m_scale) * Quaternionf::toMatrix(m_rotation) * Matrix4f::translate(m_translation) * Matrix4f::identity();

    m_computeRequest = false;
}