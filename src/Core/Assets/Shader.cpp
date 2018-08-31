#include <Core/Assets/AssetManager.hpp>

#include <Core/Context/Game.hpp>
#include <Core/Logger/Logger.hpp>

#include <fstream>

using namespace ax;

bool AssetManager::loadShader(std::string name, Path vertex, Path fragment) noexcept
{
    if(shaderExists(name))
    {
        Game::logger().log("Failed to load shader '" + name + "' because it already exists.", Logger::Warning);
        return false;
    }

    std::string vertexBuffer;
    std::ifstream vertexFile(vertex.path());
    if(!vertexFile.is_open()) return false;
    
    std::string fragmentBuffer;
    std::ifstream fragmentFile(fragment.path());
    if(!fragmentFile.is_open()) return false;

    m_shaders.emplace(name, std::make_shared<Shader>());
    Shader* newShader = m_shaders.at(name).get();

    return true;
}
bool AssetManager::unloadShader(std::string name) noexcept
{
    if(!shaderExists(name))
    {
        Game::logger().log("Failed to unload shader '" + name + "' because it does not exists.", Logger::Warning);
        return false;
    }

    if(m_textures.at(name).use_count() == 1)
    {
        m_textures.erase(name);
    }

    return true;
}
bool AssetManager::shaderExists(std::string name) noexcept
{
    return m_shaders.find(name) != m_shaders.end();
}
std::shared_ptr<const Shader> AssetManager::getShader(std::string name) noexcept
{
    try
    {
        return std::const_pointer_cast<const Shader>(m_shaders.at(name));
    }
    catch(std::out_of_range e)
    {
        Game::interrupt("Failed to access shader '" + name + "'");
    }   
}