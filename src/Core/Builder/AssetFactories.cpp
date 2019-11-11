#include <Core/Builder/AssetFactories.hpp>

using namespace ax;

IAssetFactory& AssetFactories::get(const std::string& identifier)
{
    try
    {
        return *m_factories.at(identifier).get();
    }
    catch(const std::out_of_range& e)
    {
        throw std::out_of_range(identifier);
    }    
}