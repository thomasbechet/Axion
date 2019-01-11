#include <OpenGL/Renderer/UBO/PointLightUBO.hpp>

#include <OpenGL/Renderer/Light/PointLightGL.hpp>

#include <algorithm>

using namespace ax;

PointLightUBO::PointLightUBO()
{
    glGenBuffers(1, &m_uboLights);
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboLights);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(PointLightUBOData) * POINTLIGHT_MAX_NUMBER, nullptr, GL_DYNAMIC_COPY);
    glBindBufferBase(GL_UNIFORM_BUFFER, POINTLIGHT_BINDING_POINT, m_uboLights);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glGenBuffers(1, &m_uboIndexes);
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboIndexes);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(GLuint) * (POINTLIGHT_MAX_NUMBER + 1), nullptr, GL_DYNAMIC_COPY);
    glBindBufferBase(GL_UNIFORM_BUFFER, POINTLIGHT_INDEXES_BINDING_POINT, m_uboIndexes);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
PointLightUBO::~PointLightUBO()
{
    glDeleteBuffers(1, &m_uboLights);
    glDeleteBuffers(1, &m_uboIndexes);
}

void PointLightUBO::load(PointLightGL& light) noexcept
{
    if(!m_free.empty())
    {
        light.uboIndex = m_free.back();
        m_indexes.emplace_back(m_free.back());
        m_free.pop_back();
    }
    else
    {
        light.uboIndex = m_indexes.size();
        m_indexes.emplace_back(light.uboIndex);
    }
}
void PointLightUBO::unload(PointLightGL& light) noexcept
{
    m_free.emplace_back(light.uboIndex);
    m_indexes.erase(std::remove(m_indexes.begin(), m_indexes.end(), light.uboIndex), m_indexes.end());
}

void PointLightUBO::updatePositions(IndexVector<PointLightGL>& lights, const Matrix4f& view) noexcept
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboLights);
    PointLightUBOData* p = static_cast<PointLightUBOData*>(glMapBufferRange(
        GL_UNIFORM_BUFFER,
        0,
        sizeof(PointLightUBOData) * POINTLIGHT_MAX_NUMBER,
        GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
    ));

    for(auto& light : lights)
    {
        p[light.uboIndex].position = Vector3f(view * Vector4f(light.transform->getTranslation(), 1.0f));
    }

    glUnmapBuffer(GL_UNIFORM_BUFFER);
}
void PointLightUBO::updateIndexes() noexcept
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboIndexes);
    GLuint* p = static_cast<GLuint*>(glMapBufferRange(
        GL_UNIFORM_BUFFER,
        0,
        sizeof(GLuint) * (POINTLIGHT_MAX_NUMBER + 1), 
        GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
    ));

    p[POINTLIGHT_MAX_NUMBER] = m_indexes.size();
    std::copy(m_indexes.begin(), m_indexes.end(), p);

    glUnmapBuffer(GL_UNIFORM_BUFFER);
}
void PointLightUBO::updateLight(const PointLightGL& light) noexcept
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboLights);
    PointLightUBOData* p = static_cast<PointLightUBOData*>(glMapBufferRange(
        GL_UNIFORM_BUFFER,
        sizeof(PointLightUBOData) * light.uboIndex,
        sizeof(PointLightUBOData),
        GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
    ));

    p->position = light.transform->getTranslation();
    //p->radius = 3.0f;

    glUnmapBuffer(GL_UNIFORM_BUFFER);
}