#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/System/System.hpp>
#include <Core/Input/Button.hpp>

#include <string>

namespace ax
{
    class AXION_CORE_API RenderModeSystem : public System
    {
    public:
        static const std::string name;

        void onInitialize() override;
        void onUpdate() override;
        void onTerminate() override;

    private:
        Button* m_defaultModeButton = nullptr;
        Button* m_wireframeModeButton = nullptr;
        Button* m_debugModeButton = nullptr;
    };
}