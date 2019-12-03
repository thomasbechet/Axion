#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/NonCopyable.hpp>
#include <Core/Utility/Path.hpp>

#include <vector>
#include <string>
#include <unordered_map>

namespace ax::detail
{
    class AXION_CORE_API ConfigParser : public NonCopyable
    {
    private:
        using section = std::unordered_map<std::string, std::string>;

    public:
        void parse(const Path& path) noexcept;
        bool isParsed() const noexcept;
        
        bool getBoolean(std::string section, std::string name, bool def = false);
        int getInteger(std::string section, std::string name, int def = 0);
        unsigned getUnsigned(std::string section, std::string name, unsigned def = 0);
        float getFloat(std::string section, std::string name, float def = 0.0f);
        double getDouble(std::string section, std::string name, double def = 0.0);
        std::string getString(std::string section, std::string name, std::string def = "");

    private:
        void trim(std::string& str) noexcept;
        bool checkWordValidity(std::string& str) noexcept;
        void toLower(std::string& str) noexcept;

        std::unordered_map<std::string, section> m_sections;
        bool m_parsed = false;
    };
}