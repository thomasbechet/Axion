#pragma once

#include <Core/Export.hpp>
#include <Core/Asset/AssetLoader.hpp>
#include <Core/Logger/LoggerModule.hpp>
#include <Core/Utility/Reference.ipp>
#include <Core/Context/Engine.hpp>

#include <mutex>
#include <unordered_map>
#include <sstream>
#include <iomanip>

namespace ax
{
    class AXION_CORE_API IAssetManager
    {
    public:
        virtual ~IAssetManager() = default;
        virtual void dispose() noexcept = 0;
        virtual void log() const noexcept = 0;
    };

    template<typename T>
    class AXION_CORE_API AssetManager : public IAssetManager
    {
    public:
        AssetManager(AssetLoader& loader);

        //MAIN THREAD ONLY
        Reference<T> get(const std::string& name) const noexcept;
        //ANY THREAD (validate = ONLY MAIN THREAD)
        bool load(const std::string& name, const typename T::Parameters& parameters, bool validate = false) noexcept;
        //ANY THREAD
        bool loadAsync(const std::string& name, const typename T::Parameters& parameters) noexcept;
        //ANY THREAD
        bool exists(const std::string& name) const noexcept;
        //MAIN THREAD ONLY
        bool wait(const std::string& name) const noexcept;
        //MAIN THREAD ONLY
        bool unload(const std::string& name) noexcept;

        //MAIN THREAD ONLY
        void dispose() noexcept override;
        //MAIN THREAD ONLY
        void log() const noexcept override;
        
    private:
        bool existsNotSafe(const std::string& name) const noexcept;

    private:
        std::unordered_map<std::string, std::unique_ptr<T>> m_assets;
        std::unordered_map<std::string, std::unique_ptr<ReferenceTracker<T>>> m_trackers;
        mutable std::mutex m_mutex;
        AssetLoader& m_loader;
    };
}