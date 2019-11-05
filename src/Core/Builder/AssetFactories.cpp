#include <Core/Builder/AssetFactories.hpp>

using namespace ax;

IAssetFactory& AssetFactories::get(const std::string& identifier) noexcept
{
    return *m_factories.at(identifier).get();
}