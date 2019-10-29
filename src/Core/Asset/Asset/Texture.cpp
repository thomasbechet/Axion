#include <Core/Asset/Asset/Texture.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Logger/LoggerModule.hpp>
#include <Core/Renderer/RendererModule.hpp>
#include <Core/Renderer/RendererException.hpp>
#include <Core/Asset/JsonAttributes.hpp>
#include <Core/Utility/Json.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

using namespace ax;

Texture::Texture(const std::string& name, const Parameters& parameters) : 
    Asset(name, identifier),
    m_parameters(parameters)
{
    
}

Vector2u Texture::getSize() const noexcept
{
    return m_size;
}
Texture::Format Texture::getFormat() const noexcept
{
    return m_format;
}
RendererTextureHandle Texture::getHandle() const noexcept
{
    return m_handle;
}

bool Texture::onLoad() noexcept
{
    if(!m_parameters.json.is_null() && !extractSourceFromJson()) return false;

    int width, height, bpp;
    m_data = stbi_load(m_parameters.source.c_str(), &width, &height, &bpp, 0);
    if(!m_data)
    {
        m_error = "Failed to load texture '" + m_parameters.source.str() + "'.";
        return false;
    }

    m_size.x = width;
    m_size.y = height;

    if(bpp == 3)
        m_format = Format::RGB;
    else if(bpp == 4)
        m_format = Format::RGBA;
    else if(bpp == 1)
        m_format = Format::R;

    return true;
}
bool Texture::onValidate() noexcept
{
    try
    {
        m_handle = Engine::renderer().createTexture(
            m_size,
            m_format,
            m_data
        );
    }
    catch(const RendererException& exception)
    {
        m_error = exception.what();
        stbi_image_free(m_data);
        
        return false;
    }

    return true;
}
bool Texture::onUnload() noexcept
{
    try
    {
        Engine::renderer().destroyTexture(m_handle);
    }
    catch(const RendererException& e)
    {
        m_error = e.what();

        return false;
    }

    stbi_image_free(m_data);

    return true;
}
void Texture::onError() noexcept
{
    Engine::logger().log(m_error, Severity::Warning);
}

bool Texture::extractSourceFromJson() noexcept
{
    try
    {
        if(m_parameters.json[JsonAttributes::type] != Texture::identifier)
        {
            m_error = "Loading texture without texture type attribute.";
            return false;
        }
    }
    catch(const std::exception& e)
    {
        m_error = "Texture doesn't have type attribute.";
        return false;
    }

    try
    {
        m_parameters.source = m_parameters.json[JsonAttributes::source].get<std::string>();
        return true;
    }
    catch(const std::exception& e)
    {
        m_error = "Texture doesn't have source attribute.";
        return false;
    }

    return false;
}