#include <Core/Utility/LibraryLoader.hpp>

using namespace ax;

LibraryLoader::LibraryLoader(std::string path)
{
    m_path = path;
    m_library = nullptr;
}
LibraryLoader::~LibraryLoader()
{
    if(isOpen()) doClose();
    m_path.clear();
}

bool LibraryLoader::open() noexcept
{   
    if(isOpen()) return false;
    doOpen();

    if(isOpen()) return true;
    return false;
}
void LibraryLoader::close() noexcept
{
    if(!isOpen()) return;
    doClose();
}
bool LibraryLoader::isOpen() const noexcept
{
    return m_library != nullptr;
}
std::string LibraryLoader::getPath() const noexcept
{
    return m_path;
}

#if defined(AXION_PLATFORM_WINDOWS)

void LibraryLoader::doOpen() noexcept
{

}
void LibraryLoader::doClose() noexcept
{

}
void* doGetFunction(std::string name) noexcept
{

}

#elif defined(AXION_PLATFORM_UNIX)

void LibraryLoader::doOpen() noexcept
{

}
void LibraryLoader::doClose() noexcept
{

}
void* doGetFunction(std::string name) noexcept
{

}

#elif defined(AXION_PLATFORM_APPLE)

void LibraryLoader::doOpen() noexcept
{

}
void LibraryLoader::doClose() noexcept
{

}
void* doGetFunction(std::string name) noexcept
{

}

#endif
