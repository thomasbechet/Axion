#include <OpenGL/Renderer/UBO/ShaderConstantsUBO.hpp>

#include <OpenGL/Renderer/Utility/ShaderConstants.hpp>

using namespace ax;

ShaderConstantsUBO::ShaderConstantsUBO()
{
    glGenBuffers(1, &m_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(ShaderConstantsUBOData), nullptr, GL_DYNAMIC_COPY);
    glBindBufferBase(GL_UNIFORM_BUFFER, SGC_SHADER_CONSTANTS_UBO_BINDING_POINT, m_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
ShaderConstantsUBO::~ShaderConstantsUBO()
{
    glDeleteBuffers(1, &m_ubo);
}

void ShaderConstantsUBO::setResolution(const Vector2u& resolution) noexcept
{
    m_constants.resolution = resolution;
}
void ShaderConstantsUBO::setBackgroundColor(const Color3& color) noexcept
{
    m_constants.backgroundColor = color;
}

void ShaderConstantsUBO::update() const noexcept
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    ShaderConstantsUBOData* p = static_cast<ShaderConstantsUBOData*>(glMapBufferRange(
        GL_UNIFORM_BUFFER,
        0,
        sizeof(ShaderConstantsUBOData),
        GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
    ));

    *p = m_constants;

    glUnmapBuffer(GL_UNIFORM_BUFFER);
}