#pragma once

#include <Core/Export.hpp>
#include <Core/GUI/GUILayout.hpp>
#include <Core/GUI/Widget/GUIButton.hpp>
#include <Core/GUI/Widget/GUIText.hpp>
#include <Core/Utility/IndexVector.hpp>

namespace ax
{
    class AXION_CORE_API GUI
    {
    public:
        static constexpr const Id DefaultLayout = 1;

    public:
        void initialize() noexcept;
        void terminate() noexcept;
        void update() noexcept;    
    };
}