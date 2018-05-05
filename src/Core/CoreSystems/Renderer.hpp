#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/Context/GameContext.hpp>

#include <string>

namespace ax
{
    class AXION_CORE_API Renderer
    {
    public:
        using Id = unsigned;

    public:
        virtual void init(GameContext& context) = 0;
        virtual void terminate(GameContext& context) = 0;
        virtual void draw() = 0;

        //Staticmesh
        virtual Id createStaticmesh() = 0;
        virtual Id destroyStaticmesh(Id id) = 0;
        virtual void setStaticmeshMaterial(Id id, std::string name) = 0;
        virtual void setStaticmeshTransform(Id id, ) = 0;
        virtual void setStaticmeshMesh(Id id, std::string name) = 0;
    };
}