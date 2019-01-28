#include <OpenGL/Renderer/UBO/PointLightUBO.hpp>

#include <OpenGL/Renderer/Light/PointLightGL.hpp>
#include <OpenGL/Renderer/Utility/ShaderConstants.hpp>

#include <algorithm>

using namespace ax;

PointLightUBO::PointLightUBO()
{
    glGenBuffers(1, &m_uboLights);
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboLights);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(PointLightUBOData) * POINTLIGHT_MAX_NUMBER + sizeof(GLuint), nullptr, GL_DYNAMIC_COPY);
    glBindBufferBase(GL_UNIFORM_BUFFER, POINTLIGHT_UBO_BINDING_POINT, m_uboLights);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
PointLightUBO::~PointLightUBO()
{
    glDeleteBuffers(1, &m_uboLights);
}

void PointLightUBO::load(PointLightGL& light) noexcept
{
    light.uboIndex = m_pointlights.add(PointLightUBOData());
}
void PointLightUBO::unload(PointLightGL& light) noexcept
{
    m_pointlights.remove(light.uboIndex);
}

void PointLightUBO::updateLight(const PointLightGL& light) noexcept
{
    PointLightUBOData& data = m_pointlights.get(light.uboIndex);
    data.radius = light.radius;
    data.color = light.color;
    data.intensity = light.intensity;
}
void PointLightUBO::updateMemory(IndexVector<PointLightGL>& lights, const Matrix4f& view) noexcept
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboLights);
    PointLightUBOData* p = static_cast<PointLightUBOData*>(glMapBufferRange(
        GL_UNIFORM_BUFFER,
        0,
        sizeof(PointLightUBOData) * POINTLIGHT_MAX_NUMBER + sizeof(GLuint),
        GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
    ));

    //Update light positions
    for(auto& light : lights)
    {
        m_pointlights.get(light.uboIndex).position = Vector3f(view * Vector4f(light.transform->getTranslation(), 1.0f));
    }

    std::copy(m_pointlights.begin(), m_pointlights.end(), p);

    //Update light count
    *((GLuint*)(p + POINTLIGHT_MAX_NUMBER)) = m_pointlights.size();

    glUnmapBuffer(GL_UNIFORM_BUFFER);
}