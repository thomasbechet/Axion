#pragma once

#include <Core/Export.hpp>
#include <Core/Builder/ComponentFactory.ipp>

#include <unordered_map>
#include <memory>

namespace ax
{
    class AXION_CORE_API ComponentFactories
    {
    public:
        template<typename C>
        void record() noexcept;
        template<typename C>
        void unrecord() noexcept;
        template<typename C>
        IComponentFactory& get();
        IComponentFactory& get(const std::string& identifier);

    private:
        std::unordered_map<std::string, std::unique_ptr<IComponentFactory>> m_factories;
    };
}