#include <Core/Math/Transform2D.hpp>

using namespace ax;

Transform2D::Transform2D(Vector2f translation, float rotation, Vector2f scale) :
    m_translation(translation), m_rotation(rotation), m_scale(scale)
{

}
Transform2D::~Transform2D()
{
    while(hasChild()) firstChild->detach();
    if(isAttached()) detach();
}

void Transform2D::setTranslation(float x, float y) noexcept
{
    setTranslation(Vector2f(x, y));
}
void Transform2D::setTranslation(const Vector2f& translation) noexcept
{
    m_translation = translation;
    m_requestCompute = true;
}
Vector2f Transform2D::getTranslation() const noexcept
{
    return m_translation;
}
void Transform2D::setRotation(float rotation) noexcept
{
    m_rotation = rotation;
    m_requestCompute = true;
}
float Transform2D::getRotation() const noexcept
{
    return m_rotation;
}
void Transform2D::setScale(float x, float y) noexcept
{
    setScale(Vector2f(x, y));
}
void Transform2D::setScale(const Vector2f& scale) noexcept
{
    m_scale = scale;
    m_requestCompute = true;
}
Vector2f Transform2D::getScale() const noexcept
{
    return m_scale;
}

void Transform2D::rotate(float rotation) noexcept
{
    m_rotation += rotation;
    m_requestCompute = true;
}
void Transform2D::translate(Vector2f vec) noexcept
{
    m_translation += vec;
    m_requestCompute = true;
}

void Transform2D::attachTo(Transform2D& newParent) noexcept
{
    setParent(&newParent);
}
void Transform2D::detach() noexcept
{
    setParent(nullptr);
}
bool Transform2D::isAttached() const noexcept
{
    return parent != nullptr;
}
bool Transform2D::hasChild() const noexcept
{
    return firstChild != nullptr;
}

Matrix3f Transform2D::getWorldMatrix() const noexcept
{
    return localToWorld();
}
Matrix3f Transform2D::getMatrix() const noexcept
{
    return localToParent();
}

void Transform2D::setParent(Transform2D* newParent) noexcept
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
Matrix3f Transform2D::localToWorld() const noexcept
{
    if(parent) 
        return parent->localToWorld() * localToParent();
    else 
        return localToParent();
}
Matrix3f Transform2D::localToParent() const noexcept
{
    if(m_requestCompute)
    {
        m_transform = Matrix3f::translate(m_translation) * Matrix3f::rotate(m_rotation) * Matrix3f::scale(m_scale);
        m_requestCompute = false;
    }

    return m_transform;
}