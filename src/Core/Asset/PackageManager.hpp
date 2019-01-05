#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/Asset/Package.hpp>
#include <Core/Asset/AssetReference.hpp>

namespace ax
{
    class AXION_CORE_API PackageManager
    {
    public:
        AssetReference<Package> operator()(std::string name) const noexcept;
        AssetReference<Package> create(std::string name, Path path) noexcept;
        bool destroy(std::string name) noexcept;
        bool exists(std::string name) const noexcept;

        void dispose() noexcept;
        void log() const noexcept;

    private:
        std::unordered_map<std::string, std::unique_ptr<AssetHolder<Package>>> m_packages;
    };
}