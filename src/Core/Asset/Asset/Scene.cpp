#include <Core/Asset/Asset/Scene.hpp>

using namespace ax;

Scene::Scene(const std::string& name, const Parameters& parameters) :
    Asset(name, identifier),
    m_parameters(parameters)
{

}

bool Scene::onLoad() noexcept
{
    if(!m_parameters.source.empty())
    {
        
    }

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