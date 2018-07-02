#pragma once

////////////////
//HEADERS
////////////////
#include <Core/Export.hpp>
#include <Core/Window/Window.hpp>

#include <memory>

namespace ax
{
    class AXION_CORE_API NullWindow : public Window
    {
    public:
        protected:
        void initialize() noexcept override {}
        void terminate() noexcept override {}

    public:
        bool requestGLContext() noexcept override {return false;}
        bool requestDXContext() noexcept override {return false;}
        bool requestVKContext() noexcept override {return false;}

        void setTitle(std::string title) noexcept override {}
        std::string getTitle() const noexcept override {return "";}
        void setSize(Vector2u dimensions) noexcept override {}
        Vector2u getSize() const noexcept override {return Vector2u(0, 0);}
    };
}