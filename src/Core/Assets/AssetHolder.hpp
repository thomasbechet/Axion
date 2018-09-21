#pragma once

////////////
//HEADERS
////////////
#include <Core/Export.hpp>
#include <Core/Context/Engine.hpp>

#include <memory>

namespace ax
{
    template<typename T>
    class AXION_CORE_API AssetReference;

    template<typename T>
    class AXION_CORE_API AssetHolder
    {
    public:
        friend class AssetReference<T>;

        template<typename... Args>
        AssetHolder(Args&&... args) : m_asset(args...) {}
        ~AssetHolder()
        {
            if(m_referenceCount > 0)
                Engine::interrupt("Dangling reference detected with '" + m_asset.name + "' (" + std::to_string(m_referenceCount) + " references)");
        } 

        AssetReference<T> reference() noexcept
        {
            AssetReference<T> reference;
            accessAsset(reference);
            return reference;
        }

        T* get() noexcept {return &m_asset;}
        T* operator->() const noexcept {return &m_asset;}
        size_t referenceCount() const noexcept {return m_referenceCount;}

    private:
        void accessAsset(AssetReference<T>& reference) noexcept
        {
            reference.m_asset = &m_asset;
            reference.m_holder = this;
            m_referenceCount++;
        }
        void releaseAsset(AssetReference<T>& reference) noexcept
        {     
            reference.m_asset = nullptr;
            reference.m_holder = nullptr;
            m_referenceCount--;
        }

        T m_asset;
        size_t m_referenceCount = 0;
    };
}