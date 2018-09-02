#include <Core/Assets/AssetManager.hpp>

#include <Core/Context/Game.hpp>
#include <Core/Logger/Logger.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

using namespace ax;

bool AssetManager::loadTexture(std::string name, Path path) noexcept
{
    if(textureExists(name))
    {
        Game::logger().log("Failed to load texture '" + name + "' because it already exists.", Logger::Warning);
        return false;
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
    }
    else
    {
        Game::logger().log("Failed to load texture '" + path.path() + "'", Logger::Warning);
        return false;
    }

    return true;
}
bool AssetManager::unloadTexture(std::string name) noexcept
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
bool AssetManager::textureExists(std::string name) noexcept
{
    return m_textures.find(name) != m_textures.end();
}
std::shared_ptr<const Texture> AssetManager::getTexture(std::string name) noexcept
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