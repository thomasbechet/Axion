#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>

#include <string>

namespace ax
{
    class Transform;

    class AXION_CORE_API Renderer
    {
    public:
        friend class GameContext;

    protected:
        virtual void initialize() noexcept = 0;
        virtual void terminate() noexcept = 0;
        virtual void update(double alpha) noexcept = 0;

    public:
        virtual ~Renderer(){}

        //Camera
        //virtual Id createCamera() noexcept = 0;
        //virtual void destroyCamera(Id id) noexcept = 0;
        //virtual void setCameraTransform(Id id, const Transform& transform) noexcept = 0;
        //virtual void setCameraSettings(Id id, CameraSettings settings) noexcept = 0;

        //Staticmesh
        virtual Id createStaticmesh() noexcept = 0;
        virtual void destroyStaticmesh(Id id) noexcept = 0;
        virtual void setStaticmeshMaterial(Id id, std::string name) noexcept = 0;
        virtual void setStaticmeshTransform(Id id, const Transform& transform) noexcept = 0;
        virtual void setStaticmeshMesh(Id id, std::string name) noexcept = 0;
    
        //Window resize
        virtual void updateViewport() noexcept = 0;
    };
}