#include <OpenGL/Renderer/RendererGL.hpp>

#include <Core/Renderer/RendererException.hpp>

using namespace ax;

//Shader
Id RendererGL::createShader(
    const std::string* vertex,
    const std::string* fragment
)
{
    Id id = m_content.shaders.add(ShaderGL());
    ShaderGL& shader = m_content.shaders.get(id);

    if(!shader.shader.loadShader(vertex, fragment))
    {
        m_content.shaders.remove(id);
        throw RendererException("Failed to load shader.");
    }

    return id;
}
void RendererGL::destroyShader(Id id)
{
    m_content.shaders.get(id).shader.unload();
    m_content.shaders.remove(id);
}