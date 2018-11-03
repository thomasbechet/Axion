#include <OpenGL/Renderer/RendererGL.hpp>

using namespace ax;

Id RendererGL::createPointLight()
{
    Id id = m_content.pointLights.add(PointLightGL());

    

    return id;
}
void RendererGL::destroyPointLight(Id id)
{

}
void RendererGL::setPointLightTransform(Id id, Transform* transform)
{

}
void RendererGL::setPointLightParameters(Id id, PointLightParameters parameters)
{

}