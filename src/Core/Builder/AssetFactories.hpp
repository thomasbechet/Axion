#pragma once

#include <Core/Export.hpp>
#include <Core/Builder/AssetFactory.ipp>

#include <unordered_map>
#include <memory>

namespace ax
{
    class AXION_CORE_API AssetFactories
    {
    public:
        template<typename A>
        void record() noexcept;
        template<typename A>
        void unrecord() noexcept;
        template<typename A>
        IAssetFactory& get() noexcept;
        IAssetFactory& get(const std::string& identifier) noexcept;

    private:
        std::unordered_map<std::string, std::unique_ptr<IAssetFactory>> m_factories;
    };
}