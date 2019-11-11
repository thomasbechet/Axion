#pragma once

#include <Core/Export.hpp>
#include <Core/Scene/System/System.hpp>
#include <Core/Input/Button.hpp>
#include <Core/Utility/Macro.hpp>

#include <string>

namespace ax
{
    class AXION_CORE_API RenderModeSystem : public System
    {
    public:
        SYSTEM_IDENTIFIER("render_mode")

        void onInitialize() override;
        void onUpdate() override;
        void onTerminate() override;

    private:
        Button* m_defaultModeButton = nullptr;
        Button* m_wireframeModeButton = nullptr;
        Button* m_debugModeButton = nullptr;
    };
}