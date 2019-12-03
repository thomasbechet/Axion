#pragma once

#include <core/export.hpp>
#include <core/engine/engine.hpp>
#include <core/utility/non_copyable.hpp>

#include <memory>

namespace ax
{
    template<typename type>
    class AXION_CORE_API asset_reference;

    template<typename type>
    class AXION_CORE_API asset_holder : public non_copyable
    {
    public:
        friend class asset_reference<t>;

        template<typename... args>
        asset_holder<type>(args&&... args) : m_asset(args...){}
        ~asset_holder()
        {
            if(m_reference_count > 0)
                engine::interrupt("Dangling reference detected with '" + m_asset.get_name() + "' (" + std::to_string(m_reference_count) + " references)");
        }

        asset_reference<t> reference() noexcept
        {
            asset_reference<t> reference;
            access_asset(reference);
            return reference;
        }

        type* get() noexcept {return &m_asset;}
        type* operator->() const noexcept {return &m_asset;}
        size_t reference_count() const noexcept {return m_reference_count;}

    private:
        void access_asset(asset_reference<t>& reference) noexcept
        {
            reference.m_asset = &m_asset;
            reference.m_holder = this;
            m_reference_count++;
        }
        void release_asset(asset_reference<t>& reference) noexcept
        {     
            reference.m_asset = nullptr;
            reference.m_holder = nullptr;
            m_reference_count--;
        }

        type m_asset;
        size_t m_reference_count = 0;
    };
}