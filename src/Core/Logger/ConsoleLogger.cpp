#include <Core/Logger/ConsoleLogger.hpp>

#include <ctime>
#include <iostream>
#include <iomanip>

using namespace ax;

void ConsoleLogger::log(std::string message, Severity severity) noexcept
{
    if(message != "")
    {   
        std::string color;

        switch(severity)
        {
        case INFO:
            color = "\033[36m";
        break;
        case WARNING:
            color = "\033[33m";
        break;
        case ERROR:
            color = "\033[31m";
        break;
        case FATAL:
            color = "\033[31m";
        break;
        }

        std::string sever = " ";

        switch(severity)
        {
        case INFO:
            sever = "[INFOS] ";
        break;
        case WARNING:
            sever = "[WARNING] ";
        break;
        case ERROR:
            sever = "[ERROR] ";
        break;
        case FATAL:
            sever = "[FATAL] ";
        break;
        }

        if(m_date)
        {
            auto t = std::time(nullptr);
            std::tm tm = *std::localtime(&t);

            std::cout << color << "[" << std::put_time(&tm, "%r") << "]" << sever << message << "\033[0m" << std::endl;
        }
        else
        {
            std::cout << color << sever << message << "\033[0m" << std::endl;
        }
    }
}
void ConsoleLogger::displayDate(bool toggle) noexcept
{
    m_date = toggle;
}