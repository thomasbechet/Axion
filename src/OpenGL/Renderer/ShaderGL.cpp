#include <OpenGL/Renderer/RendererGL.hpp>

#include <Core/Renderer/RendererException.hpp>

using namespace ax;

//Shader
Id RendererGL::createShader(
    const std::string* vertex,
    const std::string* fragment
)
{
    if(vertex == nullptr || fragment == nullptr)
        throw RendererException("One of the shader source is not given. Both vertex and fragment sources are required for this version.");

    Id id = m_shaders.add(ShaderGL());
    ShaderGL& shader = m_shaders.get(id);

    GLint vertexId, fragmentId;
    GLint success;
    char infoLog[512];

    const char* vertexAddr = vertex->c_str();
    const char* fragmentAddr = fragment->c_str();

    vertexId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexId, 1, &vertexAddr, nullptr);
    glCompileShader(vertexId);

    glGetShaderiv(vertexId, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        m_shaders.remove(id);
        glGetShaderInfoLog(vertexId, 512, nullptr, infoLog);
        throw RendererException(infoLog);
    }

    fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentId, 1, &fragmentAddr, nullptr);
    glCompileShader(fragmentId);

    glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        m_shaders.remove(id);
        glGetShaderInfoLog(fragmentId, 512, nullptr, infoLog);
        throw RendererException(infoLog);
    }

    shader.programId = glCreateProgram();
    glAttachShader(shader.programId, vertexId);
    glAttachShader(shader.programId, fragmentId);
    glLinkProgram(shader.programId);
    glDetachShader(shader.programId, vertexId);
    glDetachShader(shader.programId, fragmentId);

    glGetProgramiv(shader.programId, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shader.programId, 512, nullptr, infoLog);
        throw RendererException(infoLog);
    }

    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);

    return id;
}
void RendererGL::destroyShader(Id id)
{
    ShaderGL& shader = m_shaders.get(id);
    glDeleteProgram(shader.programId);
    m_shaders.remove(id);
}