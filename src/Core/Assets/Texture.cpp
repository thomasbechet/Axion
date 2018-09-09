#include <Core/Assets/Texture.hpp>

#include <Core/Context/Game.hpp>
#include <Core/Logger/Logger.hpp>
#include <Core/Renderer/Renderer.hpp>
#include <Core/Renderer/RendererException.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

using namespace ax;

std::shared_ptr<const Texture> TextureManager::loadTexture(std::string name, Path path) noexcept
{
    if(textureExists(name))
    {
        Game::logger().log("Failed to load texture '" + name + "' because it already exists.", Logger::Warning);
        return nullptr;
    }

    int width, height, bpp;
    Byte* data = stbi_load(path.c_str(), &width, &height, &bpp, 0);
    if(data != nullptr)
    {
        m_textures.emplace(name, std::make_shared<Texture>());
        Texture* texture = m_textures[name].get();
        texture->name = name;

        texture->data = data;
        texture->size.x = (unsigned)width;
        texture->size.y = (unsigned)height;

        if(bpp == 3)
            texture->format = TextureFormat::RGB;
        else if(bpp == 4)
            texture->format = TextureFormat::RGBA;

        try
        {
            texture->handle = Game::renderer().createTexture(
                texture->size,
                texture->format,
                texture->data
            );
        }
        catch(const RendererException& exception)
        {
            Game::logger().log("Failed to load texture '" + name + "' from renderer: ", Logger::Warning);
            Game::logger().log(exception.what());
            stbi_image_free(texture->data);
            m_textures.erase(name);

            return nullptr;
        }
    }
    else
    {
        Game::logger().log("Failed to load texture '" + path.path() + "'", Logger::Warning);
        return nullptr;
    }

    return true;
}
bool TextureManager::unloadTexture(std::string name) noexcept
{
    if(!textureExists(name))
    {
        Game::logger().log("Failed to unload texture '" + name + "' because it does not exists.", Logger::Warning);
        return false;
    }

    if(m_textures.at(name).use_count() != 1) return false;

    stbi_image_free(m_textures[name]->data);
    m_textures.erase(name);

    return true;
}
bool TextureManager::textureExists(std::string name) noexcept
{
    return m_textures.find(name) != m_textures.end();
}
std::shared_ptr<const Texture> TextureManager::texture(std::string name) noexcept
{
    try
    {
        return std::const_pointer_cast<const Texture>(m_textures.at(name));
    }
    catch(std::out_of_range e)
    {
        Game::interrupt("Failed to access texture '" + name + "'");
    }   
}