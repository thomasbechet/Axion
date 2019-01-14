#include <OpenGL/Renderer/Utility/ComputeShader.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Logger/Logger.hpp>

#include <fstream>
#include <streambuf>

using namespace ax;

ComputeShader::ComputeShader(std::string code)
{
    load(code);
}
ComputeShader::ComputeShader(Path file)
{
    std::ifstream computeFile(file.path());
    if(!computeFile.is_open())
        Engine::interrupt("Failed to open compute shader file");
    std::string computeBuffer{std::istreambuf_iterator<char>(computeFile), std::istreambuf_iterator<char>()};

    load(computeBuffer);
}
ComputeShader::~ComputeShader()
{
    unload();
}

void ComputeShader::use() noexcept
{
    glUseProgram(m_id);
}

void ComputeShader::load(std::string code) noexcept
{
    GLuint compute = glCreateShader(GL_COMPUTE_SHADER);
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
        Engine::interrupt("Failed to compile compute shader");
    }

    m_id = glCreateProgram();
    glAttachShader(m_id, compute);
    glLinkProgram(m_id);

    glDeleteShader(compute);
}
void ComputeShader::unload() noexcept
{
    glDeleteProgram(m_id);
}
