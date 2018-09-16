#pragma once

////////////
//HEADERS
////////////
#include <Core/Export.hpp>

#include <memory>

namespace ax
{
    template<typename T>
    class AXION_CORE_API ResourceHolder
    {
    public:
        

    private:
        std::unique_ptr<T> m_resource;
        size_t m_referenceCount = 0;
    };
}