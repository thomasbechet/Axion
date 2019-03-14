#pragma once

#include <Core/Export.hpp>
#include <Core/GUI/UIComponent.hpp>
#include <Core/GUI/UIButton.hpp>

namespace ax
{
    class AXION_CORE_API GUI
    {
    public:
        virtual ~GUI() = default;

    public:
        virtual void initialize() noexcept = 0;
        virtual void terminate() noexcept = 0;
        virtual void update() noexcept = 0;
        virtual void render() noexcept = 0;

    public:
        UIButton& createButton() noexcept;
        UIButton& createButton(UIComponent& component) noexcept;
    };
}