#include <Core/Content/Component/TransformComponent.hpp>

#include <Core/Utility/JsonUtility.hpp>

using namespace ax;

TransformComponent::TransformComponent(Entity& entity, const Json& json) :
    TransformComponent(
        entity,
        JsonUtility::readVector3f(json, "translation"),
        JsonUtility::readQuaternionf(json, "rotation"),
        JsonUtility::readVector3f(json, "scale", Vector3f(1, 1, 1))
    )
{
    auto childs = json.find("childs");
    if(childs != json.end())
    {
        for(auto& [key, item] : childs->items())
        {
            Entity& entity = Engine::scene().entity.create(key, item);
            entity.getComponent<TransformComponent>().attachTo(*this);
        }
    }
}
TransformComponent::TransformComponent(Entity& entity, Vector3f translation, Quaternionf rotation, Vector3f scale) :
    entity(entity)
{
    m_translation = translation;
    m_rotation = rotation;
    m_scale = scale;
}
TransformComponent::~TransformComponent()
{
    while(hasChild()) firstChild->detach();
    if(isAttached()) detach();
}

void TransformComponent::setTranslation(float x, float y, float z) noexcept
{
    setTranslation(Vector3f(x, y, z));
}
void TransformComponent::setTranslation(const Vector3f& translation) noexcept
{
    m_translation = translation;
    m_requestCompute = true;
}
Vector3f TransformComponent::getTranslation() const noexcept
{
    return m_translation;
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
Quaternionf TransformComponent::getRotation() const noexcept
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
Vector3f TransformComponent::getScale() const noexcept
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
    m_translation += vec;
    m_requestCompute = true;
}

Vector3f TransformComponent::getForwardVector() const noexcept
{
    return Vector3f::normalize(m_rotation * Vector3f::forward);
}
Vector3f TransformComponent::getBackwardVector() const noexcept
{
    return Vector3f::normalize(m_rotation * Vector3f::backward);
}
Vector3f TransformComponent::getLeftVector() const noexcept
{
    return Vector3f::normalize(m_rotation * Vector3f::left);
}
Vector3f TransformComponent::getRightVector() const noexcept
{
    return Vector3f::normalize(m_rotation * Vector3f::right);
}
Vector3f TransformComponent::getUpVector() const noexcept
{
    return Vector3f::normalize(m_rotation * Vector3f::up);
}
Vector3f TransformComponent::getDownVector() const noexcept
{
    return Vector3f::normalize(m_rotation * Vector3f::down);
}

void TransformComponent::attachTo(Entity& entity) noexcept
{
    setParent(&entity.getComponent<TransformComponent>());
}
void TransformComponent::attachTo(TransformComponent& parent) noexcept
{
    setParent(&parent);
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

Matrix4f TransformComponent::getWorldMatrix() const noexcept
{
    return localToWorld();
}
Matrix4f TransformComponent::getMatrix() const noexcept
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
Matrix4f TransformComponent::localToWorld() const noexcept
{
    if(parent) 
        return parent->localToWorld() * localToParent();
    else 
        return localToParent();
}
Matrix4f TransformComponent::localToParent() const noexcept
{
    if(m_requestCompute)
    {
        m_transform = Matrix4f::translate(m_translation) * Quaternionf::toMatrix(m_rotation) * Matrix4f::scale(m_scale);
        m_requestCompute = false;
    }

    return m_transform;
}