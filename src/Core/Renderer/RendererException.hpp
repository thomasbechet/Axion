#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>

#include <exception>
#include <string>

namespace ax
{
    class AXION_CORE_API RendererException : public std::exception
    {
    public:
        RendererException() {}
        RendererException(const std::string msg) : m_msg(msg) {}
        const char* what() const throw() {return m_msg.c_str();}

    private:
        std::string m_msg;
    };
}