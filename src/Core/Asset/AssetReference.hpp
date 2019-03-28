#pragma once

#include <Core/Export.hpp>
#include <Core/Asset/AssetHolder.hpp>

namespace ax
{
    template<typename T>
    class AXION_CORE_API AssetReference
    {
    public:
        friend class AssetHolder<T>;

        AssetReference<T>(){}
        AssetReference<T>(AssetHolder<T>& holder)
        {
            holder.accessAsset(*this);
        }
        AssetReference<T>(const AssetReference<T>& reference)
        {
            operator=(reference);
        }
        /*AssetReference<T>(const AssetReference<T>&& reference)
        {
            operator=(reference);
        }*/
        ~AssetReference() {reset();}

        AssetReference<T>& operator=(const AssetReference<T>& other) noexcept
        {
            reset();
            if(other.isValid())
            {
                other.m_holder->accessAsset(*this);
            }
            return *this;
        }
        /*AssetReference<T>& operator=(AssetReference<T>&& other) noexcept
        {
            std::swap(m_asset, other.m_asset);
            std::swap(m_holder, other.m_holder);
            return *this;
        }*/

        explicit operator bool() const {return isValid();}
        bool isValid() const noexcept {return m_holder != nullptr;}
        size_t referenceCount() const noexcept {return m_holder->referenceCount();}

        void reset() noexcept
        {
            if(m_holder)
            {
                m_holder->releaseAsset(*this);
            }
        }

        T* get() const noexcept {return m_asset;}
        T* operator->() const noexcept {return get();}

    private:
        AssetHolder<T>* m_holder = nullptr;
        T* m_asset = nullptr;
    };  
}