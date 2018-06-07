#include <Core/Logger/ConsoleLogger.hpp>

#include <ctime>
#include <iostream>
#include <iomanip>
#include <chrono>

#if defined(AXION_PLATFORM_WINDOWS)
    #include <windows.h>
#endif

using namespace ax;

void ConsoleLogger::log(std::string message, Severity severity) noexcept
{
    if(message != "")
    {   
        #if defined(AXION_PLATFORM_UNIX)

            std::string color = "";
            std::string sever = "";

            switch(severity)
            {
                case Severity::NONE:
                break;
                case Severity::INFO:
                    color = "\033[36m";
                    sever = "[INFO] ";
                break;
                case Severity::WARNING:
                    color = "\033[33m";
                    sever = "[WARNING] ";
                break;
                case Severity::ERROR:
                    color = "\033[31m";
                    sever = "[ERROR] ";
                break;
                case Severity::FATAL:
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
                case Severity::NONE:
                break;
                case Severity::INFO:
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
                    sever = "[INFO] ";
                break;
                case Severity::WARNING:
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                    sever = "[WARNING] ";
                break;
                case Severity::ERROR:
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                    sever = "[ERROR] ";
                break;
                case Severity::FATAL:
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
}
void ConsoleLogger::displayDate(bool toggle) noexcept
{
    m_date = toggle;
}