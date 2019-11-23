#pragma once

#include <Core/Export.hpp>

#include <unordered_map>
#include <memory>

namespace ax
{
    template<template<typename> typename Factory, typename IFactory>
    class AXION_CORE_API FactoryRecorder
    {
    public:
        template<typename T>
        void record() noexcept
        {
            m_factories[T::identifier] = std::make_unique<Factory<T>>();
        }
        template<typename T>
        void unrecord() noexcept
        {
            m_factories.erase(T::identifier);
        }
        IFactory& get(const std::string& identifier)
        {
            return *m_factories.at(identifier).get();
        }

    private:
        std::unordered_map<std::string, std::unique_ptr<IFactory>> m_factories;
    };
}