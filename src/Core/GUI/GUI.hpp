#pragma once

#include <Core/Export.hpp>

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
    };
}