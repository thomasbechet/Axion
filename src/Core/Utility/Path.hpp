#pragma once

#include <Core/Export.hpp>

#include <string>

namespace ax
{
    class AXION_CORE_API Path
    {
    public:
        Path() = default;
        Path(const char* path);
        Path(const std::string& path);

        std::string directory() const noexcept;
        std::string filename() const noexcept;
        std::string extension() const noexcept;
        std::string str() const noexcept;
        const char* c_str() const noexcept;
        bool isDirectory() const noexcept;
        bool isFilename() const noexcept;
        bool fileExists() const noexcept;
        bool empty() const noexcept;

        operator std::string() const;
        friend Path operator+(const Path& p1, const Path& p2) noexcept
        {
            return Path(p1.directory() + p2.directory() + p2.filename() + p2.extension());
        }

        static std::string sanitize(std::string path) noexcept;

    private:
        std::string m_path;
    };
}