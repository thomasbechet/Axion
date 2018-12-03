#include <Core/Assets/Material.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Assets/AssetManager.hpp>
#include <Core/Logger/Logger.hpp>
#include <Core/Renderer/Renderer.hpp>
#include <Core/Renderer/RendererMaterialParameters.hpp>
#include <Core/Renderer/RendererException.hpp>

using namespace ax;

Material(){}
Material(std::string name)
{
    m_name = name;
}
~Material()
{
    unload();
}

bool MaterialManager::load(std::string name, const MaterialParameters& params) noexcept
{
    if(isLoaded(name))
    {
        Engine::logger().log("Failed to load material '" + name + "' because it already exists.", Logger::Warning);
        return AssetReference<Material>();
    }

    if(!params.diffuseTexture.empty())
        material->diffuseTexture = Engine::assets().texture(params.diffuseTexture);
    material->diffuseUniform = params.diffuseUniform;

    if(!params.normalTexture.empty())
        material->normalTexture = Engine::assets().texture(params.normalTexture);

    if(!params.bumpTexture.empty())
        material->bumpTexture = Engine::assets().texture(params.bumpTexture);

    //Configure renderer material settings
    RendererMaterialParameters settings;

    //Diffuse
    settings.diffuseTexture = (material->diffuseTexture) ? material->diffuseTexture->handle : 0;
    settings.diffuseUniform = material->diffuseUniform;
    settings.useDiffuseTexture = (material->diffuseTexture.isValid());

    //Normal
    settings.normalTexture = (material->normalTexture) ? material->normalTexture->handle : 0;
    settings.useNormalTexture = (material->normalTexture.isValid());
    settings.bumpTexture = (material->bumpTexture) ? material->bumpTexture->handle : 0;
    settings.useBumpTexture = (material->bumpTexture.isValid());

    try
    {
        material->handle = Engine::renderer().createMaterial(settings);
    }
    catch(const RendererException& exception)
    {
        Engine::logger().log("Failed to load material '" + name + "' to renderer: ", Logger::Warning);
        Engine::logger().log(exception.what(), Logger::Warning);
        m_materials.erase(name);

        return AssetReference<Material>();
    }

    m_isLoaded = true;

    return true;
}
bool MaterialManager::unload(std::string name, bool tryUnloadTexture) noexcept
{
    if(isLoaded())
    {
        try
        {
            if(m_materials.at(name)->referenceCount() > 0) return false;
            Material* material = m_materials.at(name)->get();

            if(tryUnloadTexture)
            {
                if(material->diffuseTexture)
                {
                    std::string diffuseTexName = material->diffuseTexture->name;
                    material->diffuseTexture.reset();
                    Engine::assets().texture.unload(diffuseTexName);
                }

                if(material->normalTexture)
                {
                    std::string normalTexName = material->normalTexture->name;
                    material->normalTexture.reset();
                    Engine::assets().texture.unload(normalTexName);
                }

                if(material->bumpTexture)
                {
                    std::string bumpTexName = material->bumpTexture->name;
                    material->bumpTexture.reset();
                    Engine::assets().texture.unload(bumpTexName);
                }
            }

            Engine::renderer().destroyMaterial(material->handle);
            m_materials.erase(name);
        }
        catch(const std::out_of_range& exception)
        {
            Engine::logger().log("Failed to unload material '" + name + "' because it does not exists.", Logger::Warning);
            return false;
        }
        catch(const RendererException& exception)
        {
            Engine::logger().log("Failed to unload material '" + name + "' from renderer:", Logger::Warning);
            Engine::logger().log(exception.what(), Logger::Warning);
            return false;
        }
    }

    m_isLoaded = false;

    return true;
}

std::string Material::getName() const noexcept
{
    return m_name;
}

AssetReference<Texture> Material::getDiffuseTexture() const noexcept
{
    return m_diffuseTexture;
}
Color Material::getDiffuseColor() const noexcept
{
    return m_diffuseColor;
}
AssetReference<Texture> Material::getNormalTexture() const noexcept
{
    return m_normalTexture;
}
