#include <Core/Assets/Texture.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Logger/Logger.hpp>
#include <Core/Renderer/Renderer.hpp>
#include <Core/Renderer/RendererException.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

using namespace ax;

Texture::Texture() {}
Texture::Texture(std::string name)
{
    m_name = name;
}
Texture::~Texture()
{
    unload();
}

bool Texture::loadFromFile(Path path) noexcept
{
    unload();

    int width, height, bpp;
    m_data = stbi_load(path.c_str(), &width, &height, &bpp, 0);
    if(!m_data)
    {
        Engine::logger().log("Failed to load texture '" + path.path() + "'", Logger::Warning);
        return false;
    }

    m_size.x = width;
    m_size.y = height;

    if(bpp == 3)
        m_format = TextureFormat::RGB;
    else if(bpp == 4)
        m_format = TextureFormat::RGBA;
    else if(bpp == 1)
        m_format = TextureFormat::R;

    try
    {
        m_handle = Engine::renderer().createTexture(
            Vector2u(width, height),
            m_format,
            m_data
        );
    }
    catch(RendererException exception)
    {
        Engine::logger().log("Failed to load texture '" + m_name + "' from renderer: ", Logger::Warning);
        Engine::logger().log(exception.what());
        stbi_image_free(m_data);
        
        return false;
    }

    m_isLoaded = true;

    return true;
}
bool Texture::unload() noexcept
{
    if(isLoaded())
    {
        stbi_image_free(m_data);

        try
        {
            Engine::renderer().destroyTexture(m_handle);
        }
        catch(RendererException e)
        {
            Engine::logger().log("Failed to unload texture '" + m_name + "' from renderer: ", Logger::Warning);
            Engine::logger().log(e.what());

            return false;
        }
    }

    m_isLoaded = false;

    return true;
}
bool Texture::isLoaded() const noexcept
{
    return m_isLoaded;
}

std::string Texture::getName() const noexcept
{
    return m_name;
}
Vector2u Texture::getSize() const noexcept
{
    return m_size;
}
TextureFormat Texture::getFormat() const noexcept
{
    return m_format;
}

Id Texture::getHandle() const noexcept
{
    return m_handle;
}