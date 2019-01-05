#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/World/Component/Component.hpp>
#include <Core/Prefab/Component/TransformComponent.hpp>
#include <Core/Asset/AssetReference.hpp>
#include <Core/Asset/Model.hpp>

#include <vector>

namespace ax
{
    struct AXION_CORE_API ModelComponent : public Component
    {
    public:
        static std::string name(){return "Model";}

        ModelComponent(const Entity& entity);
        ~ModelComponent();

        void setModel(std::nullptr_t) noexcept;
        void setModel(std::string name) noexcept;
        void setModel(AssetReference<Model> model) noexcept;
        void setModel(AssetReference<Mesh> mesh) noexcept;

        void setMaterial(std::nullptr_t, Id component = 0) noexcept;
        void setMaterial(std::string name, Id component = 0) noexcept;
        void setMaterial(AssetReference<Material> material, Id component = 0) noexcept;

        TransformComponent& transform;

    private:
        std::vector<std::tuple<AssetReference<Mesh>, AssetReference<Material>, Id>> m_elements;
    };
}