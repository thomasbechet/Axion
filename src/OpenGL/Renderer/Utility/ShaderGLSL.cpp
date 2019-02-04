#include <OpenGL/Renderer/Utility/ShaderGLSL.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Logger/Logger.hpp>

#include <fstream>
#include <streambuf>
#include <regex>

using namespace ax;

ShaderGLSL::~ShaderGLSL()
{
    if(m_isLoaded) glDeleteProgram(m_handle);
}

bool ShaderGLSL::loadShader(const std::string* vertex, const std::string* fragment) noexcept
{
    if(vertex == nullptr || fragment == nullptr)
    {
        Engine::logger().log("One of the shader source is not given. Both vertex and fragment sources are required for this version.", Logger::Warning);
        return false;
    }

    GLint vertexId, fragmentId;
    GLint success;
    char infoLog[512];

    //Inject headers
    std::string vertexCode = *vertex;
    std::string fragmentCode = *fragment;
    injectHeaders(vertexCode);
    injectHeaders(fragmentCode);

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
bool ShaderGLSL::loadCompute(const std::string& computeCode) noexcept
{
    GLuint compute = glCreateShader(GL_COMPUTE_SHADER);
    std::string code = computeCode;
    injectHeaders(code);

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
bool ShaderGLSL::loadCompute(const Path path) noexcept
{
    std::ifstream computeFile(path.path());
    if(!computeFile.is_open())
    {
        Engine::logger().log("Failed to open compute shader file", Logger::Warning);
        return false;
    }
        
    std::string computeBuffer{std::istreambuf_iterator<char>(computeFile), std::istreambuf_iterator<char>()};

    return loadCompute(computeBuffer);
}

bool ShaderGLSL::isLoaded() const noexcept
{
    return m_isLoaded;
}
GLuint ShaderGLSL::getProgram() const noexcept
{
    return m_handle;
}

void ShaderGLSL::injectHeaders(std::string& code) noexcept
{
    std::regex regex("#include \\w+");
    std::smatch match;
    while(std::regex_search(code, match, regex))
    {
        std::istringstream stream(match[0]);
        std::string dummy, file;
        stream >> dummy;
        stream >> file;

        Path headerFilePath = "../shaders/headers/" + file + ".glsl";

        std::ifstream headerFile(headerFilePath);
        if(headerFile.is_open())
        {
            std::string headerCode{std::istreambuf_iterator<char>(headerFile), std::istreambuf_iterator<char>()};
            code = std::regex_replace(code, regex, headerCode, std::regex_constants::format_first_only);
        }
        else
        {
            Engine::logger().log("Failed to open file " + headerFilePath.path(), Logger::Warning);    
        }
    }
}