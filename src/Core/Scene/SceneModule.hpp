#pragma once

#include <Core/Export.hpp>
#include <Core/Scene/GameMode/GameModeManager.hpp>
#include <Core/Scene/UI/UIManager.hpp>
#include <Core/Scene/Entity/EntityManager.hpp>
#include <Core/Scene/Component/ComponentManager.hpp>
#include <Core/Scene/System/SystemManager.hpp>

#include <memory>

namespace ax
{
    class AXION_CORE_API SceneModule
    {
    public:
        GameModeManager gamemode;
        UIManager ui;
        EntityManager entity;
        ComponentManager component;
        SystemManager system;
    };
}