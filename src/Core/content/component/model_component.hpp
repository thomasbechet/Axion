#pragma once

#include <core/export.hpp>
#include <core/scene/component/component.hpp>
#include <core/content/component/transform_component.hpp>
#include <core/content/asset/model_asset.hpp>
#include <core/renderer/scene/renderer_staticmesh.hpp>
#include <core/utility/reference.hpp>

#include <vector>

namespace ax
{
    class AXION_CORE_API model_component : public component
    {
    public:
        COMPONENT_IDENTIFIER("model")
        COMPONENT_REQUIREMENTS(transform_component)
        
        model_component(Entity& entity, const Json& json);
        model_component(Entity& entity);
        ~model_component();

        void set_model(std::nullptr_t) noexcept;
        void set_model(const std::string& name) noexcept;
        void set_model(reference<_model_asset> model) noexcept;
        void set_model(reference<_mesh_asset> mesh) noexcept;

        void set_material(std::nullptr_t, id component = 0) noexcept;
        void set_material(const std::string& name, id component = 0) noexcept;
        void set_material(reference<_material_asset> material, id component = 0) noexcept;

        transform_component& transform;

    private:
        std::vector<std::tuple<reference<mesh_asset>, reference<material_asset>, renderer_staticmesh_handle>> m_elements;
    };
}