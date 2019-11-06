#pragma once

#include <Core/Export.hpp>
#include <Core/Context/Module.hpp>
#include <Core/Utility/Path.hpp>
#include <Core/Utility/Json.hpp>
#include <Core/Asset/AssetLoader.hpp>
#include <Core/Asset/AssetManager.hpp>

#include <mutex>
#include <typeinfo>
#include <typeindex>

namespace ax
{
    class AXION_CORE_API AssetModule : public Module
    {
    public:
        ~AssetModule();

    private:
        template<typename A>
        AssetManager<A>& getManager() noexcept;

        std::vector<std::unique_ptr<IAssetManager>> m_managers;
        std::unordered_map<std::type_index, size_t> m_indexes;
        std::mutex m_locationMutex;

    public:
        void dispose() noexcept;
        void log() const noexcept;

        template<typename A>
        AssetReference<A> get(const std::string& name) noexcept;
        template<typename A>
        bool load(const std::string& name, const typename A::Parameters& parameters, bool validate = false) noexcept;
        template<typename A>
        bool loadAsync(const std::string& name, const typename A::Parameters& parameters) noexcept;
        template<typename A>
        bool unload(const std::string& name) noexcept;
        template<typename A>
        bool exists(const std::string& name) noexcept;
        template<typename A>
        bool wait(const std::string& name) noexcept;
        template<typename A>
        void dispose() noexcept;
        template<typename A>
        void log() const noexcept;

        bool load(const std::string& type, const std::string& name, const Json& json = {}) noexcept;
        bool loadAsync(const std::string& type, const std::string& name, const Json& json = {}) noexcept;
        bool unload(const std::string& type, const std::string& name) noexcept;
        bool exists(const std::string& type, const std::string& name) const noexcept;
        bool wait(const std::string& type, const std::string& name) noexcept;
        void dispose(const std::string& type) noexcept;
        void log(const std::string& type) const noexcept;

        AssetLoader loader;
    };
}