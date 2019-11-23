#pragma once

#include <Core/Export.hpp>
#include <Core/Context/Module.hpp>
#include <Core/Builder/FactoryRecorder.hpp>
#include <Core/Builder/ComponentFactory.ipp>
#include <Core/Builder/SystemFactory.ipp>
#include <Core/Builder/AssetFactory.ipp>
#include <Core/Builder/GameModeFactory.ipp>

namespace ax
{
    class AXION_CORE_API BuilderModule : public Module
    {
    public:    
        FactoryRecorder<ComponentFactory, IComponentFactory> component;
        FactoryRecorder<SystemFactory, ISystemFactory> system;
        FactoryRecorder<AssetFactory, IAssetFactory> asset;
        FactoryRecorder<GameModeFactory, IGameModeFactory> gamemode;
    };
}