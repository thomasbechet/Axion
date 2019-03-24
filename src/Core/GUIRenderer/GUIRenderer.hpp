#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>

namespace ax
{
    class AXION_CORE_API GUIRenderer
    {
    public:
        virtual ~GUIRenderer() = default;

    public:
        virtual void initialize() noexcept = 0;
        virtual void terminate() noexcept = 0;
        virtual void update() noexcept = 0;

        virtual Id createLayout() noexcept = 0;
        virtual void destroyLayout(Id layout) noexcept = 0;

        virtual Id createRectangleSprite(Id layout) noexcept = 0;
        virtual void destroyRectangleSprite(Id layout, Id id) noexcept = 0; 
        virtual Id createText(Id layout) noexcept = 0;
        virtual void destroyText(Id layout, Id id) noexcept = 0;
    };
}