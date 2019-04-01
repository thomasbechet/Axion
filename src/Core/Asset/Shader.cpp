#include <Core/Asset/Shader.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Logger/Logger.hpp>
#include <Core/Renderer/Renderer.hpp>
#include <Core/Renderer/RendererException.hpp>
#include <Core/Asset/JsonAttributes.hpp>

#include <json/json.hpp>

#include <fstream>
#include <streambuf>

using namespace ax;

Shader::Shader() {}
Shader::Shader(std::string name)
{
    m_name = name;
}
Shader::~Shader()
{
    unload();
}

bool Shader::loadFromFile(Path jsonPath) noexcept
{
    unload();

    std::ifstream jsonFile(jsonPath.path());
    if(!jsonFile.is_open()) return false;
    std::string json{std::istreambuf_iterator<char>(jsonFile), std::istreambuf_iterator<char>()};

    return loadFromJson(json);
}
bool Shader::loadFromJson(const std::string& json) noexcept
{
    unload();

    nlohmann::json j = nlohmann::json::parse(json);

    auto jType = j.find(JsonAttributes::type);
    if(jType != j.end() && jType->is_string() && jType->get<std::string>() != JsonAttributes::shaderType)
    {
        Engine::logger().log("Loading shader without shader type attribute.", Logger::Warning);
        return false;
    }

    auto jVertex = j.find(JsonAttributes::vertex);
    if(jVertex == j.end() || !jVertex->is_string())
    {
        Engine::logger().log("Shader doesn't contains vertex attribute.", Logger::Warning);
        return false;
    }

    auto jFragment = j.find(JsonAttributes::fragment);
    if(jFragment == j.end() || !jFragment->is_string())
    {
        Engine::logger().log("Shader doesn't contains fragment attribute.", Logger::Warning);
        return false;
    }

    Path vertex = jVertex->get<std::string>();
    Path fragment = jFragment->get<std::string>();

    try
    {
        std::ifstream vertexFile(vertex.path());
        if(!vertexFile.is_open()) return false;
        std::string vertexBuffer{std::istreambuf_iterator<char>(vertexFile), std::istreambuf_iterator<char>()};
        
        std::ifstream fragmentFile(fragment.path());
        if(!fragmentFile.is_open()) return false;
        std::string fragmentBuffer{std::istreambuf_iterator<char>(fragmentFile), std::istreambuf_iterator<char>()};

        RendererShaderHandle handle = Engine::renderer().createShader(&vertexBuffer, &fragmentBuffer);
        
        m_vertex = vertexBuffer;
        m_fragment = fragmentBuffer;
        m_handle = handle;
    }
    catch(const RendererException& exception)
    {
        Engine::logger().log("Failed to compile shader '" + m_name + "'", Logger::Warning);
        Engine::logger().log(exception.what(), Logger::Warning);
        
        return false;
    }

    m_isLoaded = true;

    return true;
}

bool Shader::unload() noexcept
{
    if(isLoaded())
    {
        try
        {
            Engine::renderer().destroyShader(m_handle);
        }
        catch(const RendererException& exception)
        {
            Engine::logger().log("Failed to unload shader '" + m_name + "' from renderer: ", Logger::Warning);
            Engine::logger().log(exception.what(), Logger::Warning);
            
            return false;
        }
    }

    m_isLoaded = false;

    return true;
}
bool Shader::isLoaded() const noexcept
{
    return m_isLoaded;
}

std::string Shader::getName() const noexcept
{
    return m_name;
}
std::string Shader::getVertexCode() const noexcept
{
    return m_vertex;
}
std::string Shader::getFragmentCode() const noexcept
{
    return m_fragment;
}

RendererShaderHandle Shader::getHandle() const noexcept
{
    return m_handle;
}