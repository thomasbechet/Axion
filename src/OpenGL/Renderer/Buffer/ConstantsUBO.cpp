#include <OpenGL/Renderer/Buffer/ConstantsUBO.hpp>

#include <OpenGL/Renderer/Shader/ShaderConstants.hpp>

using namespace ax;

ConstantsUBO::ConstantsUBO()
{
    glGenBuffers(1, &m_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(ConstantsUBOData), nullptr, GL_DYNAMIC_COPY);
    glBindBufferBase(GL_UNIFORM_BUFFER, CONSTANTS_UBO_BINDING_POINT, m_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
ConstantsUBO::~ConstantsUBO()
{
    glDeleteBuffers(1, &m_ubo);
}

void ConstantsUBO::setResolution(const Vector2u& resolution) noexcept
{
    m_constants.resolution = resolution;
}

void ConstantsUBO::update() const noexcept
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    ConstantsUBOData* p = static_cast<ConstantsUBOData*>(glMapBufferRange(
        GL_UNIFORM_BUFFER,
        0,
        sizeof(ConstantsUBOData),
        GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
    ));

    *p = m_constants;

    glUnmapBuffer(GL_UNIFORM_BUFFER);
}