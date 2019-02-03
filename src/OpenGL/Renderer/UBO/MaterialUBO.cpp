#include <OpenGL/Renderer/UBO/MaterialUBO.hpp>

#include <OpenGL/Renderer/MaterialGL.hpp>
#include <OpenGL/Renderer/Utility/ShaderConstants.hpp>

#include <cstring>

using namespace ax;

MaterialUBO::MaterialUBO()
{
    glGenBuffers(1, &m_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(MaterialUBOData) * SGC_MATERIAL_MAX_NUMBER, nullptr, GL_DYNAMIC_COPY);
    glBindBufferBase(GL_UNIFORM_BUFFER, SGC_MATERIAL_UBO_BINDING_POINT, m_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
MaterialUBO::~MaterialUBO()
{
    glDeleteBuffers(1, &m_ubo);
}

void MaterialUBO::load(MaterialGL& material) noexcept
{
    if(!m_free.empty())
    {
        material.uboIndex = m_free.back();
        m_free.pop_back();
    }
    else
    {
        material.uboIndex = m_next;
        m_next++;
    }
}
void MaterialUBO::unload(MaterialGL& material) noexcept
{
    m_free.emplace_back(material.uboIndex);
}
void MaterialUBO::updateMaterial(const MaterialGL& material) noexcept
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);

    MaterialUBOData* p = static_cast<MaterialUBOData*>(glMapBufferRange(
        GL_UNIFORM_BUFFER,
        sizeof(MaterialUBOData) * material.uboIndex,
        sizeof(MaterialUBOData),
        GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT
    ));

    p->diffuseColor = material.diffuseColor;

    p->flags = 0;

    if(material.useDiffuseTexture)
        p->flags |= SGC_MATERIAL_USE_DIFFUSE_TEXTURE;

    if(material.useDiffuseColor)
        p->flags |= SGC_MATERIAL_USE_DIFFUSE_COLOR;

    if(material.useNormalTexture)
    {
        p->flags |= SGC_MATERIAL_USE_NORMAL_TEXTURE;
        if(material.isBumpTexture)
            p->flags |= SGC_MATERIAL_IS_BUMP_TEXTURE;
    }

    if(material.useSpecularTexture)
        p->flags |= SGC_MATERIAL_USE_SPECULAR_TEXTURE;

    glUnmapBuffer(GL_UNIFORM_BUFFER);
}