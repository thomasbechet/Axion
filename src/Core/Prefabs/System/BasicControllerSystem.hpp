#pragma once

//////////////
//HEADERS
//////////////
#include <Core/Export.hpp>
#include <Core/System/System.hpp>
#include <Core/World/Component/ComponentList.hpp>
#include <Core/Prefabs/Component/BasicControllerComponent.hpp>
#include <Core/Input/Button.hpp>
#include <Core/Input/Axis.hpp>

namespace ax
{
    class AXION_CORE_API BasicControllerSystem : public System
    {
    public:
        static std::string name() noexcept;

        void onInitialize() override;
        void onUpdate() override;
        void onTerminate() override;

    private:
        Button* m_reset = nullptr;
        Button* m_forward = nullptr;
        Button* m_backward = nullptr;
        Button* m_left = nullptr;
        Button* m_right = nullptr;
        Button* m_up = nullptr;
        Button* m_down = nullptr;
        Button* m_rotateLeft = nullptr;
        Button* m_rotateRight = nullptr;
        Axis* m_lookX = nullptr;
        Axis* m_lookY = nullptr;

        ComponentList<BasicControllerComponent>* m_list = nullptr;
    };
}