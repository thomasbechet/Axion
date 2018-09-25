#include <Core/Prefabs/Component/CameraComponent.hpp>

#include <Core/Renderer/Renderer.hpp>

using namespace ax;

CameraComponent::CameraComponent(const Entity& entity) :
    transform(entity.getComponent<TransformComponent>())
{
    m_handle = Engine::renderer().createCamera();
    Engine::renderer().setCameraTransform(m_handle, &transform);
}
CameraComponent::~CameraComponent()
{
    Engine::renderer().destroyCamera(m_handle);
}