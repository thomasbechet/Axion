#pragma once

#include <core/export.hpp>
#include <core/engine/module.hpp>
#include <core/builder/factory_recorder.hpp>
#include <core/builder/component_factory.ipp>
#include <core/builder/system_factory.ipp>
#include <core/builder/asset_factory.ipp>
#include <core/builder/gamemode_factory.ipp>

namespace ax::detail
{
    class AXION_CORE_API builder_module : public module
    {
    public:    
        void initialize() noexcept override {}
        void terminate() noexcept override {}

        factory_recorder<component_factory, icomponent_factory_interface> component;
        factory_recorder<system_factory, isystem_factory_interface> system;
        factory_recorder<asset_factory, iasset_factory_interface> asset;
        factory_recorder<gamemode_factory, igamemode_factory_interface> gamemode;
    };
}