#include <Core/Asset/Material.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Asset/AssetManager.hpp>
#include <Core/Logger/Logger.hpp>
#include <Core/Renderer/Renderer.hpp>
#include <Core/Renderer/RendererMaterialParameters.hpp>
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

bool Material::load(const MaterialParameters& params) noexcept
{
    unload();

    if(!params.diffuseTexture.empty())
        m_diffuseTexture = Engine::assets().texture(params.diffuseTexture);
    m_diffuseColor = params.diffuseColor;

    if(!params.normalTexture.empty())
        m_normalTexture = Engine::assets().texture(params.normalTexture);
    m_isBumpTexture = params.isBumpTexture;

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
bool Material::unload(bool tryDestroyTexture) noexcept
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
                    Engine::assets().texture.destroy(diffuseTexName);
                }

                if(m_normalTexture)
                {
                    std::string normalTexName = m_normalTexture->getName();
                    m_normalTexture.reset();
                    Engine::assets().texture.destroy(normalTexName);
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

Id Material::getHandle() const noexcept
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

        try
        {
            Engine::renderer().updateMaterial(m_handle, settings);
        }
        catch(const RendererException& e)
        {
            Engine::logger().log("Failed to update material '" + m_name + "'", Logger::Warning);
        }
    }
}