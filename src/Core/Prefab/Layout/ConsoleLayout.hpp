#pragma once

#include <Core/Export.hpp>
#include <Core/GUI/GUILayout.hpp>
#include <Core/GUI/Widget/GUILabel.hpp>

namespace ax
{
    class AXION_CORE_API ConsoleLayout : public GUILayout
    {
    public:
        ConsoleLayout();

        void onStart() override;
        void onStop() override;
        void onUpdate() override;

    private:
        GUILabel& m_labelVersion;
    };
}