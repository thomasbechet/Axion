#include <OpenGL/Renderer/Light/PointLightUBO.hpp>

#include <OpenGL/Renderer/Light/PointLightGL.hpp>

using namespace ax;

PointLightUBO::PointLightUBO()
{
    glGenBuffers(1, &m_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(PointLightUBOData) * POINTLIGHT_MAX_NUMBER, nullptr, GL_DYNAMIC_COPY);
    glBindBufferBase(GL_UNIFORM_BUFFER, POINTLIGHT_BINDING_POINT, m_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
PointLightUBO::~PointLightUBO()
{
    glDeleteBuffers(1, &m_ubo);
}

void PointLightUBO::load(PointLightGL& light) noexcept
{
    if(!m_free.empty())
    {
        light.uboIndex = m_free.back();
        m_free.pop_back();
    }
    else
    {
        light.uboIndex = m_next;
        m_next++;
    }
}
void PointLightUBO::unload(PointLightGL& light) noexcept
{
    m_free.emplace_back(light.uboIndex);
}
void PointLightUBO::update(const PointLightGL& light) noexcept
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);

    PointLightUBOData* p = static_cast<PointLightUBOData*>(glMapBufferRange(
        GL_UNIFORM_BUFFER,
        sizeof(PointLightUBOData) * light.uboIndex,
        sizeof(PointLightUBOData),
        GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT
    ));

    p->color = light.color;
    p->radius = light.radius;
    p->intensity = light.intensity;

    glUnmapBuffer(GL_UNIFORM_BUFFER);
}