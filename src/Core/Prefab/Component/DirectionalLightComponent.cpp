#include <Core/Prefab/Component/DirectionalLightComponent.hpp>

#include <Core/Renderer/Renderer.hpp>

using namespace ax;

DirectionalLightComponent::DirectionalLightComponent(const Entity& entity) :
    transform(entity.getComponent<TransformComponent>())
{
    m_handle = Engine::renderer().createDirectionalLight();
    Engine::renderer().setDirectionalLightTransform(m_handle, &transform);
}
DirectionalLightComponent::~DirectionalLightComponent()
{
    Engine::renderer().destroyDirectionalLight(m_handle);
}