#pragma once

////////////
//HEADERS
////////////
#include <Core/Export.hpp>

namespace ax
{
    template<typename T>
    class ResourceHolder;

    template<typename T>
    class AXION_CORE_API ResourceReference
    {
    public:
        ResourceReference(ResourceHolder<T>& holder)
        {

        }
        ResourceReference(ResourceReference<T>& reference)
        {

        }
        ResourceReference<T>& operator=(const ResourceReference<T>& other)
        {

        } 

        operator bool() const {return isValid();}
        bool isValid() const noexcept {return m_resource != nullptr;}

        void release() noexcept
        {

        }

        T* get() const noexcept {return m_resource;}
        T* operator->() const noexcept {return get();}

    private:
        ResourceHolder<T>* m_holder = nullptr;
        T* m_resource = nullptr;
    };  
}