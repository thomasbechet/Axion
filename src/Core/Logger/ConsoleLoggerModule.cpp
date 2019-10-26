#include <Core/Logger/ConsoleLoggerModule.hpp>

#include <ctime>
#include <iostream>
#include <iomanip>
#include <chrono>

#if defined(AXION_PLATFORM_WINDOWS)
    #include <windows.h>
#endif

using namespace ax;

void ConsoleLoggerModule::log(std::string message, Severity severity) noexcept
{
    #if defined(AXION_PLATFORM_UNIX)

        std::string color = "";
        std::string sever = "";

        switch(severity)
        {
            case Severity::None:
            break;
            case Severity::Info:
                color = "\033[36m";
                sever = "[INFO] ";
            break;
            case Severity::Warning:
                color = "\033[33m";
                sever = "[WARNING] ";
            break;
            case Severity::Error:
                color = "\033[31m";
                sever = "[ERROR] ";
            break;
            case Severity::Fatal:
                color = "\033[31m";
                sever = "[FATAL] ";
            break;
        }

        if(m_date)
        {
            std::time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            struct std::tm* ptm = std::localtime(&tt);
            std::cout << color << "[" << std::put_time(ptm, "%X") << "]" << sever << message << "\033[0m" << std::endl;
        }
        else
        {
            std::cout << color << sever << message << "\033[0m" << std::endl;
        }

    #elif defined(AXION_PLATFORM_WINDOWS)

        std::string sever = "";
        std::string color = "";

        switch(severity)
        {
            case Severity::None:
            break;
            case Severity::Info:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
                sever = "[INFO] ";
            break;
            case Severity::Warning:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                sever = "[WARNING] ";
            break;
            case Severity::Error:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                sever = "[ERROR] ";
            break;
            case Severity::Fatal:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                sever = "[FATAL] ";
            break;
        }

        if(m_date)
        {
            std::time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            struct std::tm* ptm = std::localtime(&tt);
            std::cout << "[" << std::put_time(ptm, "%X") << "]" << sever << message << std::endl;
        }
        else
        {
            std::cout << sever << message << std::endl;
        }

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    #endif
}
void ConsoleLoggerModule::displayDate(bool toggle) noexcept
{
    m_date = toggle;
}