#pragma once

#include <Core/Export.hpp>
//#include <Core/GUI/GUILayout.hpp>
//#include <Core/GUI/Widget/GUIButton.hpp>
//#include <Core/GUI/Widget/GUILabel.hpp>
//#include <Core/Utility/IndexVector.hpp>

namespace ax
{
    class AXION_CORE_API UIManager
    {
    public:
        void initialize() noexcept;
        void terminate() noexcept;
        void update() noexcept;    
    };
}