#include <Core/Utility/ConfigParser.hpp>

#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace ax;

void ConfigParser::parse(const Path& path) noexcept
{
    if(m_parsed) return;

    m_sections.emplace("default", std::unordered_map<std::string, std::string>()); //Create default section

    std::ifstream infile(path.str());
    if(infile.is_open())
    {
        std::string currentSection = "default";

        for(std::string line; std::getline(infile, line);)
        {
            line = line.substr(0, line.find('#', 0)); //Remove comments
            if(!line.empty())
            {
                trim(line);
                size_t delimiter;
                if((delimiter = line.find_first_of('=')) != std::string::npos) //Assignment
                {
                    std::string left = line.substr(0, delimiter);
                    trim(left);
                    toLower(left);
                    std::string right = line.substr(delimiter + 1, line.length() - delimiter);
                    trim(right);

                    m_sections[currentSection][left] = right;
                }
                else if(line.at(0) == '[' && line.at(line.length() - 1) == ']') //Maybe section
                {
                    std::string section = line.substr(1, line.length() - 2);
                    trim(section);
                    toLower(section);

                    if(checkWordValidity(section)) currentSection = section;
                }
            }
        }
    }

    m_parsed = true;
}
bool ConfigParser::isParsed() const noexcept
{
    return m_parsed;
}

bool ConfigParser::getBoolean(std::string section, std::string name, bool def)
{
    toLower(section);
    toLower(name);

    try
    {
        std::string str = m_sections.at(section).at(name);
        if(str == "0" || str == "false") return false;
        else if(str == "1" || str == "true") return true;
        else return def;
    }
    catch(std::out_of_range& e)
    {
        return def;
    }
    catch(std::invalid_argument& e)
    {
        return def;
    }
}       
int ConfigParser::getInteger(std::string section, std::string name, int def)
{
    toLower(section);
    toLower(name);

    try
    {
        return std::stol(m_sections.at(section).at(name));
    }
    catch(std::out_of_range& e)
    {
        return def;
    }
    catch(std::invalid_argument& e)
    {
        return def;
    }
}
unsigned ConfigParser::getUnsigned(std::string section, std::string name, unsigned def)
{
    toLower(section);
    toLower(name);

    try
    {
        return std::stoul(m_sections.at(section).at(name));
    }
    catch(std::out_of_range& e)
    {
        return def;
    }
    catch(std::invalid_argument& e)
    {
        return def;
    }
}
float ConfigParser::getFloat(std::string section, std::string name, float def)
{
    toLower(section);
    toLower(name);

    try
    {
        return std::stof(m_sections.at(section).at(name));
    }
    catch(std::out_of_range& e)
    {
        return def;
    }
    catch(std::invalid_argument& e)
    {
        return def;
    }
}
double ConfigParser::getDouble(std::string section, std::string name, double def)
{
    toLower(section);
    toLower(name);

    try
    {
        return std::stod(m_sections.at(section).at(name));
    }
    catch(std::out_of_range& e)
    {
        return def;
    }
    catch(std::invalid_argument& e)
    {
        return def;
    }
}
std::string ConfigParser::getString(std::string section, std::string name, std::string def)
{
    toLower(section);
    toLower(name);

    try
    {
        return m_sections.at(section).at(name);
    }
    catch(std::out_of_range& e)
    {
        return def;
    }
}

void ConfigParser::trim(std::string& str) noexcept
{
    if(str.empty()) return;

    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    str = str.substr(first, (last - first) + 1);
}
bool ConfigParser::checkWordValidity(std::string& str) noexcept
{
    for(auto it = str.begin(); it != str.end(); it++)
    {
        if(*it != '_' && !std::isalpha(*it)) return false;
    }

    return true;
}
void ConfigParser::toLower(std::string& str) noexcept
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}