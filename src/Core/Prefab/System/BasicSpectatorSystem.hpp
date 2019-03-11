#pragma once

//////////////
//HEADERS
//////////////
#include <Core/Export.hpp>
#include <Core/System/System.hpp>
#include <Core/World/Component/ComponentList.hpp>
#include <Core/Prefab/Component/BasicSpectatorComponent.hpp>
#include <Core/Input/Button.hpp>
#include <Core/Input/Axis.hpp>

namespace ax
{
    class AXION_CORE_API BasicSpectatorSystem : public System
    {
    public:
        static const std::string name;

        void onInitialize() override;
        void onUpdate() override;
        void onTerminate() override;

        void add(BasicSpectatorComponent& component) noexcept;

    private:
        Button* m_forward = nullptr;
        Button* m_backward = nullptr;
        Button* m_left = nullptr;
        Button* m_right = nullptr;
        Button* m_up = nullptr;
        Button* m_down = nullptr;
        Button* m_rotateLeft = nullptr;
        Button* m_rotateRight = nullptr;
        Button* m_slowMode = nullptr;
        Button* m_fastMode = nullptr;
        Button* m_changeMode = nullptr;
        Button* m_nextCamera = nullptr;
        Axis* m_lookX = nullptr;
        Axis* m_lookY = nullptr;
        Axis* m_zoom = nullptr;

        std::vector<BasicSpectatorComponent*> m_components;
        unsigned m_active = 0;
    };
}