#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/Renderer/Renderer.hpp>

namespace ax
{
    class AXION_CORE_API NullRenderer : public Renderer
    {
    protected:
        void initialize() noexcept override {}
        void terminate() noexcept override {}
        void update(double alpha) noexcept override {}

    public:
        //Staticmesh
        Id createStaticmesh() noexcept override {return 0;}
        void destroyStaticmesh(Id id) noexcept override {}
        void setStaticmeshMaterial(Id id, std::string name) noexcept override {}
        void setStaticmeshTransform(Id id, const Transform& transform) noexcept override {}
        void setStaticmeshMesh(Id id, std::string name) noexcept override {}

        //Window resize
        void updateViewport() noexcept override {}
    };
}