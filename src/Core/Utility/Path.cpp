#include <Core/Utility/Path.hpp>

#include <Core/Context/Engine.hpp>

#include <algorithm>
#include <fstream>
#include <regex>

#include <iostream>

using namespace ax;

Path::Path(const char* path)
{
    m_path = Path::sanitize(std::string(path));
}
Path::Path(const std::string& path)
{
    m_path = Path::sanitize(path);
}

std::string Path::directory() const noexcept
{
    size_t pos = m_path.find_last_of('/');
    if(pos != std::string::npos)
        return m_path.substr(0, pos + 1);

    return "";
}
std::string Path::filename() const noexcept
{
    std::string filename = m_path;
    size_t posBack = filename.find_last_of('/');
    if(posBack != std::string::npos)
        filename = filename.substr(posBack + 1, m_path.length());
    
    size_t posDot = filename.find_last_of('.');
    if(posDot != std::string::npos)
        filename = filename.substr(0, posDot);
        
    return filename;
}
std::string Path::extension() const noexcept
{
    size_t posDot = m_path.find_last_of('.');
    size_t posBack = m_path.find_last_of('/');
    if(posDot == std::string::npos || (posBack != std::string::npos && posBack > posDot))
        return "";
    else
        return m_path.substr(posDot, m_path.length());
}
std::string Path::path() const noexcept
{
    return m_path;
}
const char* Path::c_str() const noexcept
{
    return m_path.c_str();
}
bool Path::isDirectory() const noexcept
{
    return m_path.back() == '/';
}
bool Path::isFilename() const noexcept
{
    size_t pos = m_path.find_first_of('/');
    if(pos == std::string::npos && m_path.length() > 0)
        return true;
    else
        return false;
}
bool Path::fileExists() const noexcept
{
    if(isDirectory()) return false;

    std::ifstream f(m_path.c_str());
    return f.good();
}
bool Path::empty() const noexcept
{
    return m_path.empty();
}

Path::operator std::string() const
{
    return path();
}

std::string Path::sanitize(std::string path) noexcept
{
    //Replace constants
    path = std::regex_replace(path, std::regex("\\$ENGINE_DIR"), Engine::EngineDirectory);
    path = std::regex_replace(path, std::regex("\\$GAMEDATA_DIR"), Engine::GameDataDirectory);
    path = std::regex_replace(path, std::regex("\\$GAME_DIR"), Engine::GameDirectory);

    //Normalize path
    std::replace(path.begin(), path.end(), '\\', '/');
    if(path.front() == '/') path.erase(0, 1);

    return path;
}