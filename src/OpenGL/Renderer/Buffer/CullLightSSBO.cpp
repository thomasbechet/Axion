#include <OpenGL/Renderer/Buffer/CullLightSSBO.hpp>

#include <OpenGL/Renderer/Shader/ShaderConstants.hpp>

using namespace ax;

CullLightSSBO::CullLightSSBO(Vector2u resolution)
{
    create(resolution);
}
CullLightSSBO::~CullLightSSBO()
{
    destroy();
}

void CullLightSSBO::setResolution(Vector2u resolution) noexcept
{
    if(resolution.x > m_resolution.x || resolution.y > m_resolution.y)
    {
        destroy();
        create(resolution);
    }
}
Vector2u CullLightSSBO::getResolution() const noexcept
{
    return m_resolution;
}

Vector2u CullLightSSBO::dispatchSize(Vector2u resolution) noexcept
{
    Vector2u dispatch;
    dispatch.x = ((resolution.x + (resolution.x % CULL_TILE_SIZE)) / CULL_TILE_SIZE);
    dispatch.y = ((resolution.y + (resolution.y % CULL_TILE_SIZE)) / CULL_TILE_SIZE);

    return dispatch;
}

void CullLightSSBO::create(Vector2u resolution) noexcept
{
    m_resolution = resolution;

    glGenBuffers(1, &m_ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_ssbo);
    Vector2u dispatch = CullLightSSBO::dispatchSize(resolution);
    glBufferData(GL_SHADER_STORAGE_BUFFER, dispatch.x * dispatch.y * CULL_POINT_LIGHT_MAX_PER_TILE * sizeof(GLuint), 0, GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, CULL_POINT_LIGHT_SSBO_BINDING_POINT, m_ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}
void CullLightSSBO::destroy() noexcept
{
    glDeleteBuffers(1, &m_ssbo);
}