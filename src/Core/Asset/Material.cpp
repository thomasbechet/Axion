#include <Core/Asset/Material.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Asset/AssetManager.hpp>
#include <Core/Logger/Logger.hpp>
#include <Core/Renderer/Renderer.hpp>
#include <Core/Renderer/RendererException.hpp>

using namespace ax;

Material::Material(){}
Material::Material(std::string name)
{
    m_name = name;
}
Material::~Material()
{
    unload();
}

bool Material::loadFromFile(Path path) noexcept
{
    //TODO

    return true;
}
bool Material::loadFromJson(const std::string& json) noexcept
{
    //TODO

    return true;
}
bool Material::loadFromMemory(const MaterialParameters& parameters) noexcept
{
    unload();

    if(!parameters.diffuseTexture.empty())
        m_diffuseTexture = Engine::assets().texture(parameters.diffuseTexture);
    m_diffuseColor = parameters.diffuseColor;

    if(!parameters.normalTexture.empty())
        m_normalTexture = Engine::assets().texture(parameters.normalTexture);
    m_isBumpTexture = parameters.isBumpTexture;

    if(!parameters.specularTexture.empty())
        m_specularTexture = Engine::assets().texture(parameters.specularTexture);
    m_specularUniform = parameters.specularUniform;

    if(!parameters.shader.empty())
        m_shader = Engine::assets().shader(parameters.shader);

    try
    {
        //Basic parameters
        RendererMaterialParameters settings;
        m_handle = Engine::renderer().createMaterial(settings);
        m_isLoaded = true;
        update();
    }
    catch(const RendererException& exception)
    {
        Engine::logger().log("Failed to load material '" + m_name + "' to renderer: ", Logger::Warning);
        Engine::logger().log(exception.what(), Logger::Warning);

        return false;
    }

    return true;
}
bool Material::unload(bool tryDestroyTexture, bool tryDestroyShader) noexcept
{
    if(isLoaded())
    {
        try
        {
            if(tryDestroyTexture)
            {
                if(m_diffuseTexture)
                {
                    std::string diffuseTexName = m_diffuseTexture->getName();
                    m_diffuseTexture.reset();
                    Engine::assets().texture.unload(diffuseTexName);
                }

                if(m_normalTexture)
                {
                    std::string normalTexName = m_normalTexture->getName();
                    m_normalTexture.reset();
                    Engine::assets().texture.unload(normalTexName);
                }

                if(m_specularTexture)
                {
                    std::string specularTexName = m_specularTexture->getName();
                    m_specularTexture.reset();
                    Engine::assets().texture.unload(specularTexName);
                }
            }

            if(tryDestroyShader)
            {
                if(m_shader)
                {
                    std::string shaderName = m_shader->getName();
                    m_shader.reset();
                    Engine::assets().shader.unload(shaderName);
                }
            }

            Engine::renderer().destroyMaterial(m_handle);
        }
        catch(const std::out_of_range& exception)
        {
            Engine::logger().log("Failed to unload material '" + m_name + "' because it does not exists.", Logger::Warning);
            return false;
        }
        catch(const RendererException& exception)
        {
            Engine::logger().log("Failed to unload material '" + m_name + "' from renderer:", Logger::Warning);
            Engine::logger().log(exception.what(), Logger::Warning);
            return false;
        }
    }

    m_isLoaded = false;

    return true;
}
bool Material::isLoaded() const noexcept
{
    return m_isLoaded;
}

std::string Material::getName() const noexcept
{
    return m_name;
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

void Material::update() noexcept
{
    if(isLoaded())
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
            Engine::logger().log("Failed to update material '" + m_name + "'", Logger::Warning);
        }
    }
}