#include <OpenGL/Renderer/Asset/RendererShaderGL.hpp>
#include <OpenGL/Renderer/RendererGL.hpp>

#include <Core/Renderer/RendererException.hpp>

using namespace ax;

RendererShaderHandle RendererGL::createShader(const std::string* vertex, const std::string* fragment)
{
    Id id = m_content.shaders.add(std::make_unique<RendererShaderGL>());
    RendererShaderGL* shader = m_content.shaders.get(id).get();
    shader->id = id;

    if(!shader->shader.loadShader(vertex, fragment))
    {
        m_content.shaders.remove(id);
        throw RendererException("Failed to load shader.");
    }

    return shader;
}
void RendererGL::destroyShader(RendererShaderHandle& shaderPointer)
{
    RendererShaderGL* shader = static_cast<RendererShaderGL*>(shaderPointer);
    shader->shader.unload();
    m_content.shaders.remove(shader->id);
    shaderPointer = nullptr;
}