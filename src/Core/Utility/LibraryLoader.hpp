#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/Utility/NonCopyable.hpp>

namespace ax
{
    class AXION_CORE_API LibraryLoader : public NonCopyable
    {
    public:
        LibraryLoader(std::string path);
        ~LibraryLoader();

        bool open() noexcept;
        void close() noexcept;
        bool isOpen() const noexcept;
        std::string getPath() const noexcept;

        template<typename FuncType>
        bool getFunction(Functype& function, std::string name) noexcept
        {
            function = reinterpret_cast<FuncType>(doGetFunction(name));
            return function != nullptr;
        }

    private:
        void doOpen() noexcept;
        void doClose() noexcept;
        void* doGetFunction(std::string name) noexcept;

    private:
        void* m_library;
        std::string m_path;
    };
}