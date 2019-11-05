#include <Core/Asset/Asset/Material.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Asset/AssetModule.hpp>
#include <Core/Renderer/RendererModule.hpp>
#include <Core/Renderer/RendererException.hpp>

using namespace ax;

Material::Material(const std::string& name, const Parameters& parameters) :
    Asset(name, identifier),
    m_parameters(parameters)
{

}

AssetReference<Texture> Material::getDiffuseTexture() const noexcept
{
    return m_diffuseTexture;
}
Color3 Material::getDiffuseColor() const noexcept
{
    return m_diffuseColor;
}
void Material::setDiffuseColor(Color3 color) noexcept
{
    m_diffuseColor = color;
    update();
}

AssetReference<Texture> Material::getNormalTexture() const noexcept
{
    return m_normalTexture;
}

AssetReference<Texture> Material::getSpecularTexture() const noexcept
{
    return m_specularTexture;
}
float Material::getSpecularUniform() const noexcept
{
    return m_specularUniform;
}
void Material::setSpecularUniform(float specular) noexcept
{
    m_specularUniform = specular;
    update();
}

AssetReference<Shader> Material::getShader() const noexcept
{
    return m_shader;
}

RendererMaterialHandle Material::getHandle() const noexcept
{
    return m_handle;
}

bool Material::onLoad() noexcept
{
    return true;
}
bool Material::onValidate() noexcept
{
    if(!m_parameters.diffuseTexture.empty())
        m_diffuseTexture = Engine::asset().get<Texture>(m_parameters.diffuseTexture);
    m_diffuseColor = m_parameters.diffuseColor;

    if(!m_parameters.normalTexture.empty())
        m_normalTexture = Engine::asset().get<Texture>(m_parameters.normalTexture);
    m_isBumpTexture = m_parameters.isBumpTexture;

    if(!m_parameters.specularTexture.empty())
        m_specularTexture = Engine::asset().get<Texture>(m_parameters.specularTexture);
    m_specularUniform = m_parameters.specularUniform;

    if(!m_parameters.shader.empty())
        m_shader = Engine::asset().get<Shader>(m_parameters.shader);

    try
    {
        //Basic parameters
        RendererMaterialParameters settings;
        m_handle = Engine::renderer().createMaterial(settings);
        update();
    }
    catch(const RendererException& exception)
    {
        logValidateError(exception.what());
        return false;
    }

    return true;
}
bool Material::onUnload() noexcept
{
    try
    {
        if(m_parameters.tryDestroyTextures)
        {
            if(m_diffuseTexture)
            {
                std::string diffuseTexName = m_diffuseTexture->getName();
                m_diffuseTexture.reset();
                Engine::asset().unload<Texture>(diffuseTexName);
            }

            if(m_normalTexture)
            {
                std::string normalTexName = m_normalTexture->getName();
                m_normalTexture.reset();
                Engine::asset().unload<Texture>(normalTexName);
            }

            if(m_specularTexture)
            {
                std::string specularTexName = m_specularTexture->getName();
                m_specularTexture.reset();
                Engine::asset().unload<Texture>(specularTexName);
            }
        }

        if(m_parameters.tryDestroyShader)
        {
            if(m_shader)
            {
                std::string shaderName = m_shader->getName();
                m_shader.reset();
                Engine::asset().unload<Shader>(shaderName);
            }
        }

        Engine::renderer().destroyMaterial(m_handle);
    }
    catch(const RendererException& exception)
    {
        logUnloadError(exception.what());
        return false;
    }

    return true;
}

void Material::update() noexcept
{
    //Configure renderer material settings
    RendererMaterialParameters settings;

    //Diffuse
    settings.diffuseTexture = (m_diffuseTexture) ? m_diffuseTexture->getHandle() : 0;
    settings.diffuseColor = m_diffuseColor;
    settings.useDiffuseTexture = (m_diffuseTexture.isValid());

    //Normal
    settings.normalTexture = (m_normalTexture) ? m_normalTexture->getHandle() : 0;
    settings.useNormalTexture = (m_normalTexture.isValid());
    settings.isBumpTexture = m_isBumpTexture;

    //Specular
    settings.specularTexture = (m_specularTexture) ? m_specularTexture->getHandle() : 0;
    settings.specularUniform = m_specularUniform;
    settings.useSpecularTexture = (m_specularTexture.isValid());       

    //Shader
    settings.shader = (m_shader) ? m_shader->getHandle() : 0;

    try
    {
        m_handle->update(settings);
    }
    catch(const RendererException& e)
    {
        Engine::logger().log("Failed to update asset <" + Material::identifier + "> '" + getName() + "'", Severity::Warning);
    }
}