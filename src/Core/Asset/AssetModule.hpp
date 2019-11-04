#pragma once

#include <Core/Export.hpp>
#include <Core/Context/Module.hpp>
#include <Core/Utility/Path.hpp>
#include <Core/Math/Geometry/Vertex.hpp>
#include <Core/Asset/AssetLoader.hpp>
#include <Core/Asset/AssetManager.hpp>
#include <Core/Asset/Asset/Texture.hpp>
#include <Core/Asset/Asset/Mesh.hpp>
#include <Core/Asset/Asset/Material.hpp>
#include <Core/Asset/Asset/Model.hpp>
#include <Core/Asset/Asset/Package.hpp>
#include <Core/Asset/Asset/Shader.hpp>
#include <Core/Asset/Asset/Scene.hpp>

namespace ax
{
    class AXION_CORE_API AssetModule : public Module
    {
    public:
        AssetModule();
        ~AssetModule();

        void dispose() noexcept;
        void log() const noexcept;

        template<typename T>
        AssetReference<T> get(const std::string& name) const noexcept;
        template<typename T>
        bool load(const std::string& name, const typename T::Parameters& parameters) noexcept;
        template<typename T>
        bool loadAsync(const std::string& name, const typename T::Parameters& parameters) noexcept;
        template<typename T>
        bool unload(const std::string& name) noexcept;
        template<typename T>
        bool exists(const std::string& name) noexcept;
        template<typename T>
        bool wait(const std::string& name) noexcept;
        template<typename T>
        void dispose() noexcept;
        template<typename T>
        void log() const noexcept;

        bool load(const std::string& type, const std::string& name, const Json& json = {}) noexcept;
        bool loadAsync(const std::string& type, const std::string& name, const Json& json = {}) noexcept;
        bool unload(const std::string& type, const std::string& name) noexcept;
        bool exists(const std::string& type, const std::string& name) const noexcept;
        bool wait(const std::string& type, const std::string& name) noexcept;
        void dispose(const std::string& type) noexcept;
        void log(const std::string& type) const noexcept;

        AssetLoader loader;

    private:


    };
}