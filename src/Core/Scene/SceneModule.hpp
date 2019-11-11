#pragma once

#include <Core/Export.hpp>
#include <Core/Scene/GameMode/GameModeManager.hpp>
#include <Core/Scene/UI/UIManager.hpp>
#include <Core/Scene/Entity/EntityManager.hpp>
#include <Core/Scene/Component/ComponentManager.hpp>
#include <Core/Scene/System/SystemManager.hpp>
#include <Core/Content/Asset/Scene.hpp>
#include <Core/Utility/Reference.ipp>

#include <memory>

namespace ax
{
    class AXION_CORE_API SceneModule
    {
    public:    
        ComponentManager component;
        EntityManager entity;
        SystemManager system;
        UIManager ui;
        GameModeManager gamemode;

    public:
        void open(const std::string& scene) noexcept;
        void open(Reference<Scene> scene) noexcept;

        Reference<Scene> m_activeScene;
    };
}