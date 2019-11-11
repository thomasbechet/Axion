#pragma once

#include <Core/Export.hpp>
#include <Core/Scene/Component/Component.hpp>
#include <Core/Content/Component/TransformComponent.hpp>
#include <Core/Content/Asset/Model.hpp>
#include <Core/Renderer/Scene/RendererStaticmesh.hpp>
#include <Core/Utility/Reference.hpp>

#include <vector>

namespace ax
{
    struct AXION_CORE_API ModelComponent : public Component
    {
    public:
        COMPONENT_IDENTIFIER("model")
        COMPONENT_REQUIREMENT(TransformComponent)
        
        ModelComponent(const Entity& entity, const Json& json);
        ModelComponent(const Entity& entity);
        ~ModelComponent();

        void setModel(std::nullptr_t) noexcept;
        void setModel(const std::string& name) noexcept;
        void setModel(Reference<Model> model) noexcept;
        void setModel(Reference<Mesh> mesh) noexcept;

        void setMaterial(std::nullptr_t, Id component = 0) noexcept;
        void setMaterial(const std::string& name, Id component = 0) noexcept;
        void setMaterial(Reference<Material> material, Id component = 0) noexcept;

        TransformComponent& transform;

    private:
        std::vector<std::tuple<Reference<Mesh>, Reference<Material>, RendererStaticmeshHandle>> m_elements;
    };
}