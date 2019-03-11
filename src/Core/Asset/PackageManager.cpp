#include <Core/Asset/PackageManager.hpp>

#include <Core/Logger/Logger.hpp>

using namespace ax;

AssetReference<Package> PackageManager::operator()(std::string name) const noexcept
{
    try
    {
        return m_packages.at(name)->reference();
    }
    catch(std::out_of_range e)
    {
        Engine::interrupt("Failed to access package '" + name + "'");
    }
}
AssetReference<Package> PackageManager::loadFromFile(std::string name, Path path) noexcept
{
    if(exists(name))
    {
        Engine::logger().log("Failed to load package '" + name + "' because it already exists.", Logger::Warning);
        return AssetReference<Package>();
    }

    m_packages.emplace(name, std::make_unique<AssetHolder<Package>>(name));
    if(!m_packages.at(name)->get()->loadFromFile(path))
    {
        m_packages.erase(name);
        return AssetReference<Package>();
    }

    return m_packages.at(name)->reference();
}
AssetReference<Package> PackageManager::loadFromJson(std::string name, const std::string& json) noexcept
{
    if(exists(name))
    {
        Engine::logger().log("Failed to load package '" + name + "' because it already exists.", Logger::Warning);
        return AssetReference<Package>();
    }

    m_packages.emplace(name, std::make_unique<AssetHolder<Package>>(name));
    if(!m_packages.at(name)->get()->loadFromJson(json))
    {
        m_packages.erase(name);
        return AssetReference<Package>();
    }

    return m_packages.at(name)->reference();
}
bool PackageManager::unload(std::string name) noexcept
{
    if(!exists(name))
    {
        Engine::logger().log("Failed to unload package '" + name + "' because it does not exists.", Logger::Warning);
        return false;
    }

    if(m_packages.at(name)->referenceCount() > 0) return false;

    Package* package = m_packages.at(name)->get();

    package->unload();

    m_packages.erase(name);

    return true;
}
bool PackageManager::exists(std::string name) const noexcept
{
    return m_packages.find(name) != m_packages.end();
}

void PackageManager::dispose() noexcept
{
    std::vector<std::string> keys;
    keys.reserve(m_packages.size());
    for(auto& it : m_packages)
        keys.emplace_back(it.first);

    for(auto it : keys) unload(it);
}
void PackageManager::log() const noexcept
{
    Engine::logger().log("[PACKAGE]", Logger::Info);
    
    for(auto& it : m_packages)
    {
        Engine::logger().log(" \\_ " + it.first, Logger::Info);
    }
}