#include <Core/Math/Transform.hpp>

using namespace ax;

Transform::Transform(Vector3f position, Quaternionf rotation, Vector3f scale) 
    : m_translation(position), m_rotation(rotation), m_scale(scale)
{

}
Transform::~Transform()
{
    while(hasChild()) firstChild->detach();
    if(isAttached()) detach();
}

void Transform::setTranslation(float x, float y, float z) noexcept
{
    setTranslation(Vector3f(x, y, z));
}
void Transform::setTranslation(const Vector3f& translation) noexcept
{
    m_translation = translation;
    m_requestCompute = true;
}
Vector3f Transform::getTranslation() noexcept
{
    return m_translation;
}
void Transform::setRotation(float angle, const Vector3f& axis) noexcept
{
    setRotation(Quaternionf(angle, axis));
}
void Transform::setRotation(const Quaternionf& rotation) noexcept
{
    m_rotation = rotation;
    m_requestCompute = true;
}
Quaternionf Transform::getRotation() noexcept
{
    return m_rotation;
}
void Transform::setScale(float x, float y, float z) noexcept
{
    setScale(Vector3f(x, y, z));
}
void Transform::setScale(const Vector3f& scale) noexcept
{
    m_scale = scale;
    m_requestCompute = true;
}
Vector3f Transform::getScale() noexcept
{
    return m_scale;
}   

void Transform::rotate(float angle, Vector3f axis) noexcept
{
    m_rotation *= Quaternionf(angle, axis);
    m_requestCompute = true;
}
void Transform::translate(Vector3f vec) noexcept
{
    m_translation += vec;
    m_requestCompute = true;
}

Vector3f Transform::getForwardVector() noexcept
{
    return Vector3f::normalize(m_rotation * Vector3f::forward);
}
Vector3f Transform::getBackwardVector() noexcept
{
    return Vector3f::normalize(m_rotation * Vector3f::backward);
}
Vector3f Transform::getLeftVector() noexcept
{
    return Vector3f::normalize(m_rotation * Vector3f::left);
}
Vector3f Transform::getRightVector() noexcept
{
    return Vector3f::normalize(m_rotation * Vector3f::right);
}
Vector3f Transform::getUpVector() noexcept
{
    return Vector3f::normalize(m_rotation * Vector3f::up);
}
Vector3f Transform::getDownVector() noexcept
{
    return Vector3f::normalize(m_rotation * Vector3f::down);
}

void Transform::attachTo(Transform& newParent) noexcept
{
    setParent(&newParent);
}
void Transform::detach() noexcept
{
    setParent(nullptr);
}
bool Transform::isAttached() const noexcept
{
    return parent != nullptr;
}
bool Transform::hasChild() const noexcept
{   
    return firstChild != nullptr;
}

Matrix4f Transform::getWorldMatrix() noexcept
{
    return localToWorld();
}
Matrix4f Transform::getMatrix() noexcept
{
    return localToParent();
}

void Transform::setParent(Transform* newParent) noexcept
{
    if(parent) //Remove from existing parent
    {
        if(prevSibling) prevSibling->nextSibling = nextSibling;
        else parent->firstChild = nextSibling; //No previous, next become first

        if(nextSibling) nextSibling->prevSibling = prevSibling;

        prevSibling = nullptr;
        nextSibling = nullptr;
        parent = nullptr;
    }

    parent = newParent;

    if(parent) //Add to new parent
    {
        if(parent->firstChild) parent->firstChild->prevSibling = this;
        nextSibling = parent->firstChild;
        parent->firstChild = this;
    }
}
Matrix4f Transform::localToWorld() noexcept
{
    if(parent) 
        return parent->localToWorld() * localToParent();
    else 
        return localToParent();
}
Matrix4f Transform::localToParent() noexcept
{
    if(m_requestCompute)
    {
        m_transform = Matrix4f::translate(m_translation) * Quaternionf::toMatrix(m_rotation) * Matrix4f::scale(m_scale);
        m_requestCompute = false;
    }

    return m_transform;
}