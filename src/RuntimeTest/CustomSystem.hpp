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

        m_pointlights.reserve(MAX_X * MAX_Y);
        for(int x = 0; x < MAX_X; x++)
        {
            for(int y = 0; y < MAX_Y; y++)
            {
                ax::Entity& pointLight = ax::Engine::world().entities().create();
                ax::TransformComponent* lightTransform = &pointLight.addComponent<ax::TransformComponent>();
                lightTransform->setTranslation(0.0f + x * 5.0f, 0.2f, 50.0f + y * 5.0f);
                m_pointlights.emplace_back(lightTransform);
                pointLight.addComponent<ax::PointLightComponent>(pointLight).setRadius(5.0f);
                pointLight.addComponent<ax::UVSphereComponent>(pointLight, 0.2f);
            }
        }
    }

    void onUpdate() override
    {
        float delta = ax::Engine::context().getDeltaTime().asSeconds();
        m_time += delta;
        m_transform->setRotation(ax::radians(1.0f) * m_time, ax::Vector3f(1.0f, 0.0f, 0.0f));

        for(int x = 0; x < MAX_X; x++)
        {
            for(int y = 0; y < MAX_Y; y++)
            {
                ax::TransformComponent* component = m_pointlights.at(y * MAX_X + x);
                ax::Vector3f trans = component->getTranslation();
                trans.y = 1.2f + std::cos(m_time + x * y);
                component->setTranslation(trans);
            }
        }

        if(spawnButton->isJustPressed())
        {
            ax::Entity& light = ax::Engine::world().entities().create();
            light.addComponent<ax::TransformComponent>().setTranslation(m_spawn->getTranslation());
            light.addComponent<ax::PointLightComponent>(light).setRadius(10);
        }
    }

private:
    std::vector<ax::TransformComponent*> m_pointlights;
    //int MAX_X = 32;
    //int MAX_Y = 32;
    int MAX_X = 2;
    int MAX_Y = 2;

    ax::TransformComponent* m_transform;
    ax::TransformComponent* m_spawn;
    float m_time = 0.0f;

    ax::Button* spawnButton;
};