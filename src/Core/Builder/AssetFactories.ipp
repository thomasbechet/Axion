#pragma once

#include <Core/Builder/AssetFactories.hpp>

namespace ax
{
    template<typename A>
    void AssetFactories::record() noexcept
    {
        m_factories[A::identifier] = std::make_unique<AssetFactory<A>>();
    }
    template<typename A>
    void AssetFactories::unrecord() noexcept
    {
        m_factories.erase(A::identifier);
    }
    template<typename A>
    IAssetFactory& AssetFactories::get()
    {
        try
        {
            return *m_factories.at(A::identifier).get();
        }
        catch(const std::out_of_range& e)
        {
            throw std::out_of_range(A::identifier);
        }
    }
}