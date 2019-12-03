#pragma once

#include <core/export.hpp>

#include <unordered_map>
#include <memory>

namespace ax
{
    template<template<typename> typename factory, typename factory_interface>
    class AXION_CORE_API factory_recorder
    {
    public:
        template<typename type>
        void record() noexcept
        {
            m_factories[type::identifier] = std::make_unique<factory<type>>();
        }
        template<typename type>
        void unrecord() noexcept
        {
            m_factories.erase(type::identifier);
        }
        factory_interface& get(const std::string& identifier)
        {
            return *m_factories.at(identifier).get();
        }

    private:
        std::unordered_map<std::string, std::unique_ptr<factory_interface>> m_factories;
    };
}