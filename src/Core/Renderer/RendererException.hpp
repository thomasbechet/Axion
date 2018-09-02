#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>

#include <exception>

namespace ax
{
    class AXION_CORE_API RendererException : public std::exception
    {
    public:
        RendererException() : m_msg(nullptr) {}
        RendererException(const char* msg) : m_msg(msg) {}
        const char* what() const throw() {return m_msg;}

    private:
        const char* m_msg;
    };
}