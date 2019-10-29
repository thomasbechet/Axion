#pragma once

#include <Core/Builder/SystemFactory.ipp>

#include <unordered_map>
#include <memory>

namespace ax
{
    class AXION_CORE_API SystemFactories
    {
    public:
        template<typename S>
        void record() noexcept;
        template<typename S>
        void unrecord() noexcept;
        template<typename S>
        ISystemFactory& get() noexcept;

    private:
        std::unordered_map<std::string, std::unique_ptr<ISystemFactory>> m_factories;
    };
}