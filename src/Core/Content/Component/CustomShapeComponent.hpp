#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Math/Geometry/Shape.hpp>
#include <Core/Scene/Entity/Entity.hpp>
#include <Core/Content/Component/TransformComponent.hpp>

namespace ax
{
    class AXION_CORE_API CustomShapeComponent : public Component
    {
    public:
        COMPONENT_IDENTIFIER("custom_shape")
        COMPONENT_REQUIREMENTS(TransformComponent)
        
        CustomShapeComponent(Entity& entity, const Json& json);
        CustomShapeComponent(Entity& entity);
        ~CustomShapeComponent();

        void setVertices(const std::vector<Vertex>& points) noexcept;
        void setVertices(const std::vector<Vector3f>& points) noexcept;
        const std::vector<Vertex>& getVertices() const noexcept;

        TransformComponent& transform;

    private:
        //Id m_handle;
        std::vector<Vertex> m_vertices;
    };
}