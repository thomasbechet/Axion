#pragma once

#include <Core/Export.hpp>
#include <Core/Scene/System/System.hpp>
#include <Core/Input/Button.hpp>

#include <string>

namespace ax
{
    class AXION_CORE_API BasicWindowSystem : public System
    {
    public:
        static const std::string type;

        void onInitialize() override;
        void onUpdate() override;
        void onTerminate() override;

    private:
        Button* m_fullscreenButton = nullptr;
        Button* m_borderlessButton = nullptr;
        Button* m_closeButton = nullptr;
        Button* m_vsyncButton = nullptr;
    };
}