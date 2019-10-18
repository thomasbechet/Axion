#include <Core/Asset/Asset/Scene.hpp>

using namespace ax;

const std::string Scene::type = "Scene";

Scene::Scene(std::string name, const Parameters& parameters) :
    Asset(name, type),
    m_parameters(parameters)
{

}

bool Scene::onLoad() noexcept
{
    return true;
}
bool Scene::onValidate() noexcept
{
    return true;
}
bool Scene::onUnload() noexcept
{
    return true;
}
void Scene::onError() noexcept
{

}