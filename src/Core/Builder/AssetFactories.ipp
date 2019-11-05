#pragma once

#include <Core/Builder/AssetFactories.hpp>

namespace ax
{
    template<typename A>
    void AssetFactories::record() noexcept
    {
        m_factories[C::identifier] = std::make_unique<AssetFactory<C>>();
    }
    template<typename A>
    void AssetFactories::unrecord() noexcept
    {
        m_factories.erase(A::identifier);
    }
    template<typename A>
    IAssetFactory& AssetFactories::get() noexcept
    {
        return *m_factories.at(A::identifier).get();
    }
}