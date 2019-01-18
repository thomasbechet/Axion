#include <OpenGL/Renderer/UBO/DirectionalLightUBO.hpp>

#include <OpenGL/Renderer/Light/DirectionalLightGL.hpp>
#include <OpenGL/Renderer/Utility/ShaderConstants.hpp>

#include <algorithm>

using namespace ax;

DirectionalLightUBO::DirectionalLightUBO()
{
    glGenBuffers(1, &m_uboLights);
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboLights);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(DirectionalLightUBOData) * POINTLIGHT_MAX_NUMBER + sizeof(GLuint), nullptr, GL_DYNAMIC_COPY);
    glBindBufferBase(GL_UNIFORM_BUFFER, POINTLIGHT_UBO_BINDING_POINT, m_uboLights);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
DirectionalLightUBO::~DirectionalLightUBO()
{
    glDeleteBuffers(1, &m_uboLights);
}

void DirectionalLightUBO::load(DirectionalLightGL& light) noexcept
{
    light.uboIndex = m_pointlights.add(PointLightUBOData());
}
void DirectionalLightUBO::unload(DirectionalLightGL& light) noexcept
{
    m_pointlights.remove(light.uboIndex);
}

void DirectionalLightUBO::updateLight(const DirectionalLightGL& light) noexcept
{
    m_pointlights.get(light.uboIndex).position = light.transform->getTranslation();
}
void DirectionalLightUBO::updatePositions(IndexVector<DirectionalLightGL>& lights, const Matrix4f& view) noexcept
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboLights);
    DirectionalLightUBOData* p = static_cast<DirectionalLightUBOData*>(glMapBufferRange(
        GL_UNIFORM_BUFFER,
        0,
        sizeof(DirectionalLightUBOData) * POINTLIGHT_MAX_NUMBER + sizeof(GLuint),
        GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
    ));

    //Update light positions
    for(auto& light : lights)
    {
        m_directionalLights.get(light.uboIndex).position = Vector3f(view * Vector4f(light.transform->getTranslation(), 1.0f));
    }

    std::copy(m_directionalLights.begin(), m_directionalLights.end(), p);

    //Update light count
    *((GLuint*)(p + POINTLIGHT_MAX_NUMBER)) = m_directionalLights.size();

    glUnmapBuffer(GL_UNIFORM_BUFFER);
}