#pragma once

#include <Core/Export.hpp>
#include <Core/Context/Module.hpp>
#include <Core/Builder/ComponentFactories.ipp>
#include <Core/Builder/SystemFactories.ipp>
#include <Core/Builder/AssetFactories.hpp>

#include <unordered_map>

namespace ax
{
    class AXION_CORE_API BuilderModule : public Module
    {
    public:
        ComponentFactories component;
        SystemFactories system;
        AssetFactories asset;
    };
}