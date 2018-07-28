#include <Core/Prefabs/Component/TransformComponent.hpp>

using namespace ax;

TransformComponent::TransformComponent(Vector3f position, Quaternionf rotation, Vector3f scale) 
    : m_position(position), m_rotation(rotation), m_scale(scale)
{

}
TransformComponent::~TransformComponent()
{
    while(hasChild()) firstChild->detach();
    if(isAttached()) detach();
}

void TransformComponent::setPosition(float x, float y, float z) noexcept
{
    setPosition(Vector3f(x, y, z));
}
void TransformComponent::setPosition(const Vector3f& position) noexcept
{
    m_position = position;
    m_requestCompute = true;
}
Vector3f TransformComponent::getPosition() noexcept
{
    return m_position;
}
void TransformComponent::setRotation(float angle, const Vector3f& axis) noexcept
{
    setRotation(Quaternionf(angle, axis));
}
void TransformComponent::setRotation(const Quaternionf& rotation) noexcept
{
    m_rotation = rotation;
    m_requestCompute = true;
}
Quaternionf TransformComponent::getRotation() noexcept
{
    return m_rotation;
}
void TransformComponent::setScale(float x, float y, float z) noexcept
{
    setScale(Vector3f(x, y, z));
}
void TransformComponent::setScale(const Vector3f& scale) noexcept
{
    m_scale = scale;
    m_requestCompute = true;
}
Vector3f TransformComponent::getScale() noexcept
{
    return m_scale;
}   

void TransformComponent::rotate(float angle, Vector3f axis) noexcept
{
    m_rotation *= Quaternionf(angle, axis);
    m_requestCompute = true;
}
void TransformComponent::translate(Vector3f vec) noexcept
{
    m_position += vec;
    m_requestCompute = true;
}

Vector3f TransformComponent::getForwardVector() noexcept
{
    return Vector3f::normalize(m_rotation * Vector3f::forward);
}
Vector3f TransformComponent::getBackwardVector() noexcept
{
    return Vector3f::normalize(m_rotation * Vector3f::backward);
}
Vector3f TransformComponent::getLeftVector() noexcept
{
    return Vector3f::normalize(m_rotation * Vector3f::left);
}
Vector3f TransformComponent::getRightVector() noexcept
{
    return Vector3f::normalize(m_rotation * Vector3f::right);
}
Vector3f TransformComponent::getUpVector() noexcept
{
    return Vector3f::normalize(m_rotation * Vector3f::up);
}
Vector3f TransformComponent::getDownVector() noexcept
{
    return Vector3f::normalize(m_rotation * Vector3f::down);
}

void TransformComponent::attachTo(TransformComponent& newParent) noexcept
{
    setParent(&newParent);
}
void TransformComponent::attachTo(const Entity& entity) noexcept
{
    setParent(&entity.getComponent<TransformComponent>());
}
void TransformComponent::detach() noexcept
{
    setParent(nullptr);
}
bool TransformComponent::isAttached() const noexcept
{
    return parent != nullptr;
}
bool TransformComponent::hasChild() const noexcept
{   
    return firstChild != nullptr;
}

Matrix4f TransformComponent::getWorldMatrix() noexcept
{
    return localToWorld();
}
Matrix4f TransformComponent::getMatrix() noexcept
{
    return localToParent();
}

void TransformComponent::setParent(TransformComponent* newParent) noexcept
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
Matrix4f TransformComponent::localToWorld() noexcept
{
    if(parent) 
        return parent->localToWorld() * localToParent();
    else 
        return localToParent();
}
Matrix4f TransformComponent::localToParent() noexcept
{
    if(m_requestCompute)
    {
        m_transform = Matrix4f::translate(m_position) * Quaternionf::toMatrix(m_rotation) * Matrix4f::scale(m_scale);
        m_requestCompute = false;
    }

    return m_transform;
}