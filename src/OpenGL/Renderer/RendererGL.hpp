#pragma once

/////////////
//HEADERS
/////////////
#include <OpenGL/Export.hpp>
#include <Core/Renderer/Renderer.hpp>

namespace ax
{
    class AXION_GL_API RendererGL : public Renderer
    {
    protected:
        void initialize() noexcept override;
        void terminate() noexcept override;
        void update(double alpha) noexcept override;

    public:
        Id createStaticmesh() noexcept override;
        void destroyStaticmesh(Id id) noexcept override;
        void setStaticmeshMaterial(Id id, std::string name) noexcept override;
        void setStaticmeshTransform(Id id, const Transform& trans) noexcept override;
        void setStaticmeshMesh(Id id, std::string name) noexcept override;
    
        void updateViewport() noexcept override;
    };
}