#include <OpenGL/Renderer/Shader/ShaderGLSL.hpp>

#include <OpenGL/Renderer/Shader/ShaderConstants.hpp>
#include <Core/Context/Engine.hpp>
#include <Core/Logger/Logger.hpp>

#include <fstream>
#include <streambuf>
#include <regex>

using namespace ax;

bool ShaderGLSL::loadShader(const std::string* vertex, const std::string* fragment) noexcept
{
    if(vertex == nullptr || fragment == nullptr)
    {
        Engine::logger().log("One of the shader source is not given. Both vertex and fragment sources are required for this version.", Logger::Warning);
        return false;
    }

    std::string vertexCode = *vertex;
    std::string fragmentCode = *fragment;

    injectConstants(vertexCode);
    injectConstants(fragmentCode);

    return compileShader(vertexCode, fragmentCode);
}   
bool ShaderGLSL::loadCompute(const std::string& compute) noexcept
{
    std::string computeCode = compute;

    injectConstants(computeCode);

    return compileCompute(computeCode);
}
void ShaderGLSL::unload() noexcept
{
    if(m_isLoaded) glDeleteProgram(m_handle);
    m_isLoaded = false;
}

bool ShaderGLSL::isLoaded() const noexcept
{
    return m_isLoaded;
}
GLuint ShaderGLSL::getProgram() const noexcept
{
    return m_handle;
}

bool ShaderGLSL::compileShader(const std::string& vertexCode, const std::string& fragmentCode) noexcept
{
    GLint vertexId, fragmentId;
    GLint success;
    char infoLog[512];

    const char* vertexAddr = vertexCode.c_str();
    const char* fragmentAddr = fragmentCode.c_str();

    vertexId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexId, 1, &vertexAddr, nullptr);
    glCompileShader(vertexId);

    glGetShaderiv(vertexId, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexId, 512, nullptr, infoLog);
        Engine::logger().log(std::string(infoLog), Logger::Warning);
        return false;
    }

    fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentId, 1, &fragmentAddr, nullptr);
    glCompileShader(fragmentId);

    glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentId, 512, nullptr, infoLog);
        Engine::logger().log(std::string(infoLog), Logger::Warning);
        return false;
    }

    m_handle = glCreateProgram();
    glAttachShader(m_handle, vertexId);
    glAttachShader(m_handle, fragmentId);
    glLinkProgram(m_handle);
    glDetachShader(m_handle, vertexId);
    glDetachShader(m_handle, fragmentId);

    glGetProgramiv(m_handle, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(m_handle, 512, nullptr, infoLog);
        Engine::logger().log(std::string(infoLog), Logger::Warning);
        return false;
    }

    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);

    m_isLoaded = true;

    return true;
}
bool ShaderGLSL::compileCompute(const std::string& computeCode) noexcept
{
    GLuint compute = glCreateShader(GL_COMPUTE_SHADER);
    std::string code = computeCode;

    const char* ptr = code.c_str();
    glShaderSource(compute, 1, &ptr, NULL);
    glCompileShader(compute);

    GLint success;
    char infoLog[512];
    glGetShaderiv(compute, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(compute, 512, nullptr, infoLog);

        Engine::logger().log(std::string(infoLog), Logger::Warning);
        return false;
    }

    m_handle = glCreateProgram();
    glAttachShader(m_handle, compute);
    glLinkProgram(m_handle);

    glDeleteShader(compute);

    m_isLoaded = true;

    return true;
}

void ShaderGLSL::injectConstants(std::string& code) noexcept
{
    replaceConstantInteger(code, MATERIAL_UBO_BINDING_POINT, "MATERIAL_UBO_BINDING_POINT");
    replaceConstantInteger(code, MATERIAL_MAX_NUMBER, "MATERIAL_MAX_NUMBER");
    replaceConstantInteger(code, MATERIAL_USE_DIFFUSE_TEXTURE, "MATERIAL_USE_DIFFUSE_TEXTURE");
    replaceConstantInteger(code, MATERIAL_USE_DIFFUSE_COLOR, "MATERIAL_USE_DIFFUSE_COLOR");
    replaceConstantInteger(code, MATERIAL_USE_NORMAL_TEXTURE, "MATERIAL_USE_NORMAL_TEXTURE");
    replaceConstantInteger(code, MATERIAL_IS_BUMP_TEXTURE, "MATERIAL_IS_BUMP_TEXTURE");
    replaceConstantInteger(code, MATERIAL_USE_SPECULAR_TEXTURE, "MATERIAL_USE_SPECULAR_TEXTURE");

    replaceConstantInteger(code, CAMERA_UBO_BINDING_POINT, "CAMERA_UBO_BINDING_POINT");

    replaceConstantInteger(code, POINT_LIGHT_UBO_BINDING_POINT, "POINT_LIGHT_UBO_BINDING_POINT");
    replaceConstantInteger(code, POINT_LIGHT_MAX_NUMBER, "POINT_LIGHT_MAX_NUMBER");
    
    replaceConstantInteger(code, DIRECTIONAL_LIGHT_UBO_BINDING_POINT, "DIRECTIONAL_LIGHT_UBO_BINDING_POINT");
    replaceConstantInteger(code, DIRECTIONAL_LIGHT_MAX_NUMBER, "DIRECTIONAL_LIGHT_MAX_NUMBER");

    replaceConstantInteger(code, USE_LIGHT_CULLING, "USE_LIGHT_CULLING");
    replaceConstantInteger(code, CULL_POINT_LIGHT_SSBO_BINDING_POINT, "CULL_POINT_LIGHT_SSBO_BINDING_POINT");
    replaceConstantInteger(code, CULL_POINT_LIGHT_MAX_PER_TILE, "CULL_POINT_LIGHT_MAX_PER_TILE");
    replaceConstantInteger(code, CULL_TILE_SIZE, "CULL_TILE_SIZE");

    replaceConstantInteger(code, CONSTANTS_UBO_BINDING_POINT, "CONSTANTS_UBO_BINDING_POINT");

    //LOCATIONS AND BINDINGS//
    replaceConstantInteger(code, MATERIAL_INDEX_LOCATION, "MATERIAL_INDEX_LOCATION");
    replaceConstantInteger(code, MVP_MATRIX_LOCATION, "MVP_MATRIX_LOCATION");
    replaceConstantInteger(code, TRANSFORM_MATRIX_LOCATION, "TRANSFORM_MATRIX_LOCATION");
    replaceConstantInteger(code, NORMALTOVIEW_MATRIX_LOCATION, "NORMALTOVIEW_MATRIX_LOCATION");
    replaceConstantInteger(code, GUI_COLOR_LOCATION, "GUI_COLOR_LOCATION");

    replaceConstantInteger(code, DIFFUSE_TEXTURE_BINDING, "DIFFUSE_TEXTURE_BINDING");
    replaceConstantInteger(code, NORMAL_TEXTURE_BINDING, "NORMAL_TEXTURE_BINDING");
    replaceConstantInteger(code, SPECULAR_TEXTURE_BINDING, "SPECULAR_TEXTURE_BINDING");
    replaceConstantInteger(code, GUI_TEXTURE_BINDING, "GUI_TEXTURE_BINDING");

    replaceConstantInteger(code, GBUFFER_NORMAL_TEXTURE_BINDING, "GBUFFER_NORMAL_TEXTURE_BINDING");
    replaceConstantInteger(code, GBUFFER_DEPTH_TEXTURE_BINDING, "GBUFFER_DEPTH_TEXTURE_BINDING");
}
void ShaderGLSL::replaceConstantInteger(std::string& code, int value, std::string name) noexcept
{
    code = std::regex_replace(code, std::regex("\\$" + name), std::to_string(value), std::regex_constants::format_default);
}