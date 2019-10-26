#include <OpenGL/Renderer/Buffer/ConstantsUBO.hpp>

#include <OpenGL/Renderer/Shader/ShaderConstants.hpp>
#include <Core/Context/Engine.hpp>
#include <Core/Window/WindowModule.hpp>

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

void ConstantsUBO::setViewportResolution(const Vector2u& resolution) noexcept
{
    m_constants.viewportResolution = resolution;
}
void ConstantsUBO::setWindowSize(const Vector2u& size) noexcept
{
    m_constants.windowSize = size;
}

void ConstantsUBO::update() noexcept
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    ConstantsUBOData* p = static_cast<ConstantsUBOData*>(glMapBufferRange(
        GL_UNIFORM_BUFFER,
        0,
        sizeof(ConstantsUBOData),
        GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
    ));

    m_constants.windowSize = Engine::window().getSize();
    *p = m_constants;

    glUnmapBuffer(GL_UNIFORM_BUFFER);
}