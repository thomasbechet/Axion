#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/CoreSystems/Renderer.hpp>

namespace ax
{
    class AXION_CORE_API NullRenderer : public Renderer
    {
    public:
        void init() noexcept override {};
        void terminate() noexcept override {};
        void update() noexcept override {};

        //Staticmesh
        Id createStaticmesh() noexcept override {return 0;};
        void destroyStaticmesh(Id id) noexcept override {};
        void setStaticmeshMaterial(Id id, std::string name) noexcept override {};
        void setStaticmeshTransform(Id id, Transform& transform) noexcept override {};
        void setStaticmeshMesh(Id id, std::string name) noexcept override {};
    };
}