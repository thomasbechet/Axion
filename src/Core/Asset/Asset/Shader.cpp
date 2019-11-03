#include <Core/Asset/Asset/Shader.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Renderer/RendererModule.hpp>
#include <Core/Renderer/RendererException.hpp>
#include <Core/Asset/JsonAttributes.hpp>
#include <Core/Utility/Json.hpp>

#include <fstream>
#include <streambuf>

using namespace ax;

Shader::Shader(const std::string& name, const Parameters& parameters) :
    Asset(name, identifier),
    m_parameters(parameters)
{

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

bool Shader::onLoad() noexcept
{
    Json json;
    if(!m_parameters.source.empty())
    {
        std::ifstream jsonFile(m_parameters.source.str());
        if(!jsonFile.is_open())
        {
            logLoadError("Failed to open file '" + m_parameters.source.str() + "'");
            return false;
        }
        std::string str((std::istreambuf_iterator<char>(jsonFile)),
                         std::istreambuf_iterator<char>());
        json = Json::parse(str);
    }
    else
    {
        json = m_parameters.json;
    }

    try
    {
        if(json[JsonAttributes::type] != Shader::identifier)
        {
             logLoadError("Loading <" + Shader::identifier + "> without '" + Shader::identifier + "' value for '" + JsonAttributes::type + "' attribute");
            return false;
        }
    }
    catch(const Json::parse_error& e)
    {
        logLoadError(e.what());
        return false;
    }

    try
    {
        auto jVertex = json[JsonAttributes::vertex];
        try
        {
            auto jFragment = json[JsonAttributes::fragment];

            Path vertex = jVertex.get<std::string>();
            Path fragment = jFragment.get<std::string>();

            std::ifstream vertexFile(vertex.str());
            if(!vertexFile.is_open())
            {
                m_error = "Failed to open vertex file '" + vertex.str() + "'";
                return false;
            }
            m_vertex.assign(
                (std::istreambuf_iterator<char>(vertexFile)),
                (std::istreambuf_iterator<char>())
            );

            std::ifstream fragmentFile(fragment.str());
            if(!fragmentFile.is_open())
            {
                m_error = "Failed to open fragment file '" + fragment.str() + "'";
                return false;
            }
            m_fragment.assign(
                (std::istreambuf_iterator<char>(fragmentFile)),
                (std::istreambuf_iterator<char>())
            );
        }
        catch(const std::exception& e)
        {
            m_error = "Shader doesn't contains fragment attribute.";
            return false;
        }
    }
    catch(const std::exception& e)
    {
        m_error = "Shader doesn't contains vertex attribute.";
        return false;
    }

    return true;
}
bool Shader::onValidate() noexcept
{
    try
    {
        m_handle = Engine::renderer().createShader(&m_vertex, &m_fragment);
    }
    catch(const RendererException& exception)
    {     
        m_error = exception.what();
        return false;
    }

    return true;
}
bool Shader::onUnload() noexcept
{
    try
    {
        Engine::renderer().destroyShader(m_handle);
    }
    catch(const RendererException& exception)
    {
        m_error = exception.what();
        return false;
    }

    return true;
}
void Shader::onError() noexcept
{
    Engine::logger().log(m_error, Severity::Warning);
}
