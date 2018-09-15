#include <Core/Assets/Shader.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Logger/Logger.hpp>
#include <Core/Renderer/Renderer.hpp>
#include <Core/Renderer/RendererException.hpp>

#include <fstream>
#include <streambuf>

using namespace ax;

std::shared_ptr<const Shader> ShaderManager::operator()(std::string name) const noexcept
{
    try
    {
        return std::const_pointer_cast<const Shader>(m_shaders.at(name));
    }
    catch(std::out_of_range e)
    {
        Engine::interrupt("Failed to access shader '" + name + "'");
    }   
}
std::shared_ptr<const Shader> ShaderManager::load(std::string name, Path vertex, Path fragment) noexcept
{
    if(isLoaded(name))
    {
        Engine::logger().log("Failed to load shader '" + name + "' because it already exists.", Logger::Warning);
        return nullptr;
    }

    try
    {
        std::ifstream vertexFile(vertex.path());
        if(!vertexFile.is_open()) return nullptr;
        std::string vertexBuffer{std::istreambuf_iterator<char>(vertexFile), std::istreambuf_iterator<char>()};
        
        std::ifstream fragmentFile(fragment.path());
        if(!fragmentFile.is_open()) return nullptr;
        std::string fragmentBuffer{std::istreambuf_iterator<char>(fragmentFile), std::istreambuf_iterator<char>()};

        Id handle = Engine::renderer().createShader(&vertexBuffer, &fragmentBuffer);

        m_shaders.emplace(name, std::make_shared<Shader>());
        Shader* newShader = m_shaders.at(name).get();
        
        newShader->name = name;
        newShader->vertex = vertexBuffer;
        newShader->fragment = fragmentBuffer;
        newShader->handle = handle;
    }
    catch(const RendererException& exception)
    {
        Engine::logger().log("Failed to compile shader '" + name + "'", Logger::Warning);
        Engine::logger().log(exception.what(), Logger::Warning);
        return nullptr;
    }

    return m_shaders.at(name);
}
bool ShaderManager::unload(std::string name) noexcept
{
    if(!isLoaded(name))
    {
        Engine::logger().log("Failed to unload shader '" + name + "' because it does not exists.", Logger::Warning);
        
        return false;
    }

    if(m_shaders.at(name).use_count() != 1) return false;

    try
    {
        Engine::renderer().destroyShader(m_shaders.at(name).get()->handle);
        m_shaders.erase(name);
    }
    catch(const RendererException& exception)
    {
        Engine::logger().log("Failed to unload shader '" + name + "' from renderer: ", Logger::Warning);
        Engine::logger().log(exception.what(), Logger::Warning);
        
        return false;
    }

    return true;
}
bool ShaderManager::isLoaded(std::string name) const noexcept
{
    return m_shaders.find(name) != m_shaders.end();
}

void ShaderManager::dispose() noexcept
{
    std::vector<std::string> keys;
    keys.reserve(m_shaders.size());
    for(auto it : m_shaders)
        keys.emplace_back(it.second->name);

    for(auto it : keys) unload(it);
}
void ShaderManager::log() const noexcept
{
    Engine::logger().log("[    SHADER   ]", Logger::Info);
    
    for(auto it = m_shaders.begin(); it != m_shaders.end(); it++)
    {
        Engine::logger().log("- " + it->second.get()->name, Logger::Info);
    }
}