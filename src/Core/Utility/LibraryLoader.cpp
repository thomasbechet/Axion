#include <Core/Utility/LibraryLoader.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Logger/Logger.hpp>

using namespace ax;

LibraryLoader::~LibraryLoader()
{
    if(isOpen()) doClose();
}

bool LibraryLoader::open(Path path) noexcept
{   
    if(isOpen()) return false;

    m_path = path;
    doOpen();

    if(!isOpen()) return false;
    return true;
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
Path LibraryLoader::getPath() const noexcept
{
    return m_path;
}

#if defined(AXION_PLATFORM_WINDOWS)

    #include <windows.h>

    void LibraryLoader::doOpen() noexcept
    {
        #if defined(__MINGW32__)
        std::string path = m_path.directory() + "lib" + m_path.filename() + ".dll";
        #elif defined(_MSC_VER)
        std::string path = m_path.directory() + m_path.filename() + ".dll";
        #endif

        m_library = LoadLibraryA(path.c_str());
        if(!m_library)
            Engine::logger().log("Failed to load dynamic library " + path, Logger::Warning);
    }
    void LibraryLoader::doClose() noexcept
    {
        if(m_library)
        {
            UINT oldMode = SetErrorMode(SEM_FAILCRITICALERRORS);
            FreeLibrary(static_cast<HMODULE>(m_library));
            SetErrorMode(oldMode);
            m_library = nullptr;
        }
    }
    void* LibraryLoader::doGetFunction(std::string name) noexcept
    {
        void* result = nullptr;

        if(m_library)
        {
            UINT oldMode = SetErrorMode(SEM_FAILCRITICALERRORS);
            result = reinterpret_cast<void*>(GetProcAddress(static_cast<HMODULE>(m_library), name.c_str()));
            SetErrorMode(oldMode);
        }
        else Engine::logger().log("Failed to load function <" + name + "> because dynamic library is not loaded", Logger::Severity::Warning);

        return result;
    }

#elif defined(AXION_PLATFORM_UNIX)

    #include <dlfcn.h>

    void LibraryLoader::doOpen() noexcept
    {
        std::string path = m_path.directory() + "lib" + m_path.filename() + ".so";
        m_library = dlopen(path.c_str(), RTLD_LAZY);

        if(!m_library)
            Engine::logger().log("Failed to load dynamic library " + path, Logger::Warning);
    }
    void LibraryLoader::doClose() noexcept
    {
        if(m_library)
        {
            dlclose(m_library);
            m_library = nullptr;
        }
    }
    void* LibraryLoader::doGetFunction(std::string name) noexcept
    {
        void* result = nullptr;
        
        if(m_library)
        {
            result = reinterpret_cast<void*>(dlsym(m_library, name.c_str()));
        }
        else Engine::logger().log("Failed to load function <" + name + "> because dynamic library is not loaded", Logger::Severity::Warning);
    
        return result;
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
