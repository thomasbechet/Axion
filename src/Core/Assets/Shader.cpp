#include <Core/Assets/AssetManager.hpp>

#include <Core/Context/Game.hpp>
#include <Core/Logger/Logger.hpp>

#include <fstream>
#include <streambuf>

using namespace ax;

bool AssetManager::loadShader(std::string name, Path vertex, Path fragment) noexcept
{
    if(shaderExists(name))
    {
        Game::logger().log("Failed to load shader '" + name + "' because it already exists.", Logger::Warning);
        return false;
    }

    try
    {
        std::ifstream vertexFile(vertex.path());
        if(!vertexFile.is_open()) return false;
        std::string vertexBuffer(std::istreambuf_iterator<char>(vertexFile), std::istreambuf_iterator<char>());
        
        std::ifstream fragmentFile(fragment.path());
        if(!fragmentFile.is_open()) return false;
        std::string fragmentBuffer(std::istreambuf_iterator<char>(fragmentFile), std::istreambuf_iterator<char>());

        ID handle = Game::renderer().loadShader(vertexBuffer, fragmentBuffer);

        m_shaders.emplace(name, std::make_shared<Shader>());
        Shader* newShader = m_shaders.at(name).get();
        
        newShader->vertex = vertexBuffer;
        newShader->fragment = fragmentBuffer;
        newShader->handle = handle;
    }
    catch(const RendererException& exception)
    {
        Game::logger().log("Failed to compile shader '" + name + "'", Logger::Warning);
        return false;
    }

    return true;
}
bool AssetManager::unloadShader(std::string name) noexcept
{
    if(!shaderExists(name))
    {
        Game::logger().log("Failed to unload shader '" + name + "' because it does not exists.", Logger::Warning);
        return false;
    }

    if(m_textures.at(name).use_count() != 1) return false;

    try
    {
        Game::renderer().unloadShader(m_textures.at(name).get()->handle);
        m_textures.erase(name);
    }
    catch(const RendererException& exception)
    {
        return false;
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