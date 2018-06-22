#pragma once

///////////////
//HEADERS
///////////////
#include <string>

#include <Core/Export.hpp>

namespace ax
{
    class Transform;

    class AXION_CORE_API Renderer
    {
    public:
        using Id = unsigned;

    public:
        virtual ~Renderer(){}

        virtual void init() noexcept = 0;
        virtual void terminate() noexcept = 0;
        virtual void update() noexcept = 0;

        //Staticmesh
        virtual Id createStaticmesh() noexcept = 0;
        virtual void destroyStaticmesh(Id id) noexcept = 0;
        virtual void setStaticmeshMaterial(Id id, std::string name) noexcept = 0;
        virtual void setStaticmeshTransform(Id id, Transform& transform) noexcept = 0;
        virtual void setStaticmeshMesh(Id id, std::string name) noexcept = 0;
    };
}