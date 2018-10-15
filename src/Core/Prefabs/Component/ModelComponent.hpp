#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/World/Component/Component.hpp>
#include <Core/Prefabs/Component/TransformComponent.hpp>
#include <Core/Assets/AssetReference.hpp>
#include <Core/Assets/Model.hpp>

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

        TransformComponent& transform;

    private:
        void loadModelChilds() noexcept;
        void unloadModelChilds() noexcept;

        AssetReference<Model> m_model;
        std::vector<Entity*> m_childs;
    };
}