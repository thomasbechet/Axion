#pragma once

#include <Core/System/System.hpp>

class CustomSystem : public ax::System
{
public:
    static std::string name(){return "CustomSystem";}

    void setTransform(ax::TransformComponent* transform)
    {
        m_transform = transform;
    }

    void setSpawnTransform(ax::TransformComponent* transform)
    {
        m_spawn = transform;
    }

    void onStart() override
    {
        spawnButton = &ax::Engine::input().addButton("test");
        spawnButton->bind(ax::Keyboard::C);
    }

    void onUpdate() override
    {
        float delta = ax::Engine::context().getDeltaTime().asSeconds();
        m_time += delta;
        m_transform->setRotation(ax::radians(1.0f) * m_time, ax::Vector3f(1.0f, 0.0f, 0.0f));

        if(spawnButton->isJustPressed())
        {
            ax::Entity& light = ax::Engine::world().entities().create();
            light.addComponent<ax::TransformComponent>().setTranslation(m_spawn->getTranslation());
            light.addComponent<ax::PointLightComponent>(light);
        }
    }

private:
    ax::TransformComponent* m_transform;
    ax::TransformComponent* m_spawn;
    float m_time = 0.0f;

    ax::Button* spawnButton;
};