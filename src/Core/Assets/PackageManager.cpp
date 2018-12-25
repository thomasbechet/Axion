#include <Core/Assets/PackageManager.hpp>

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
AssetReference<Package> PackageManager::create(std::string name, Path path) noexcept
{
    m_packages.emplace(name, std::make_unique<AssetHolder<Package>>(name));

    m_packages.at(name)->get()->loadFromFile(path);

    return m_packages.at(name)->reference();
}
bool PackageManager::destroy(std::string name) noexcept
{
    if(!exists(name))
    {
        Engine::logger().log("Failed to destroy package '" + name + "' because it does not exists.", Logger::Warning);
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

    for(auto it : keys) destroy(it);
}
void PackageManager::log() const noexcept
{
    Engine::logger().log("[PACKAGE]", Logger::Info);
    
    for(auto& it : m_packages)
    {
        Engine::logger().log(" \\_ " + it.first, Logger::Info);
    }
}