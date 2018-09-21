#pragma once

////////////
//HEADERS
////////////
#include <Core/Export.hpp>
#include <Core/Assets/AssetHolder.hpp>

namespace ax
{
    template<typename T>
    class AXION_CORE_API AssetReference
    {
    public:
        friend class AssetHolder<T>;

        AssetReference(){}
        AssetReference(AssetHolder<T>& holder)
        {
            holder.accessAsset(*this);
        }
        AssetReference(const AssetReference<T>& reference)
        {
            operator=(reference);
        }
        AssetReference<T>& operator=(const AssetReference<T>& other)
        {
            if(isValid()) m_holder->releaseAsset(*this);
            if(other.isValid()) other.m_holder->accessAsset(*this);
            return *this;
        }
        ~AssetReference() {reset();}

        operator bool() const {return isValid();}
        bool isValid() const noexcept {return m_holder != nullptr;}

        void reset() noexcept
        {
            if(m_holder) m_holder->releaseAsset(*this); 
        }

        T* get() const noexcept {return m_asset;}
        T* operator->() const noexcept {return get();}

    private:
        AssetHolder<T>* m_holder = nullptr;
        T* m_asset = nullptr;
    };  
}