#include <OpenGL/Renderer/UBO/DirectionalLightUBO.hpp>

#include <OpenGL/Renderer/Light/DirectionalLightGL.hpp>
#include <OpenGL/Renderer/Utility/ShaderConstants.hpp>

#include <algorithm>

using namespace ax;

DirectionalLightUBO::DirectionalLightUBO()
{
    glGenBuffers(1, &m_uboLights);
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboLights);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(DirectionalLightUBOData) * SGC_DIRECTIONALLIGHT_MAX_NUMBER + sizeof(GLuint), nullptr, GL_DYNAMIC_COPY);
    glBindBufferBase(GL_UNIFORM_BUFFER, SGC_DIRECTIONALLIGHT_UBO_BINDING_POINT, m_uboLights);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
DirectionalLightUBO::~DirectionalLightUBO()
{
    glDeleteBuffers(1, &m_uboLights);
}

void DirectionalLightUBO::load(DirectionalLightGL& light) noexcept
{
    light.uboIndex = m_directionalLights.add(DirectionalLightUBOData());
}
void DirectionalLightUBO::unload(DirectionalLightGL& light) noexcept
{
    m_directionalLights.remove(light.uboIndex);
}

void DirectionalLightUBO::updateLight(const DirectionalLightGL& light) noexcept
{
    
}
void DirectionalLightUBO::updateMemory(IndexVector<DirectionalLightGL>& lights, const Matrix4f& view) noexcept
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboLights);
    DirectionalLightUBOData* p = static_cast<DirectionalLightUBOData*>(glMapBufferRange(
        GL_UNIFORM_BUFFER,
        0,
        sizeof(DirectionalLightUBOData) * SGC_DIRECTIONALLIGHT_MAX_NUMBER + sizeof(GLuint),
        GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
    ));

    //Update light positions
    for(auto& light : lights)
    {
        m_directionalLights.get(light.uboIndex).direction = Matrix3f(view) * light.transform->getForwardVector();
    }

    std::copy(m_directionalLights.begin(), m_directionalLights.end(), p);

    //Update light count
    *((GLuint*)(p + SGC_DIRECTIONALLIGHT_MAX_NUMBER)) = m_directionalLights.size();

    glUnmapBuffer(GL_UNIFORM_BUFFER);
}