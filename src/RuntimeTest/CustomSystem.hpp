#pragma once

#include <Core/System/System.hpp>

class CustomSystem : public ax::System
{
public:
    static const std::string name;

    void setSpawnTransform(ax::TransformComponent* transform)
    {
        m_spawn = transform;
    }

    void onStart() override
    {
        spawnButton = &ax::Engine::input().addButton("test");
        spawnButton->bind(ax::Keyboard::C);

        ax::Material::Parameters lightMaterialParameters;
        lightMaterialParameters.shader = "light_emission";
        ax::Engine::assets().material.load("light_emission_material", lightMaterialParameters);
        ax::AssetReference<ax::Material> m = ax::Engine::assets().material("light_emission_material");

        m_pointlights.reserve(MAX_X * MAX_Y);
        for(int x = 0; x < MAX_X; x++)
        {
            for(int y = 0; y < MAX_Y; y++)
            {
                ax::Entity& pointLight = ax::Engine::world().entity.create();
                ax::TransformComponent* lightTransform = &pointLight.addComponent<ax::TransformComponent>();
                lightTransform->setTranslation(0.0f + x * 5.0f, 0.2f, 50.0f + y * 5.0f);
                m_pointlights.emplace_back(lightTransform);
                ax::PointLightComponent& pointLightComponent = pointLight.addComponent<ax::PointLightComponent>(pointLight);
                pointLightComponent.setRadius(5.0f);
                int r = rand() % 256;
                int g = rand() % 256;
                int b = rand() % 256;
                pointLightComponent.setColor(ax::Color3(r, g, b));
                pointLight.addComponent<ax::UVSphereComponent>(pointLight, 0.2f).setMaterial(m);
            }
        }

        //Rotation light
        ax::Entity light = ax::Engine::world().entity.create();
        m_lightTransform = &light.addComponent<ax::TransformComponent>();
        ax::PointLightComponent& pointlight = light.addComponent<ax::PointLightComponent>(light);
        pointlight.setRadius(30.0f);
        light.addComponent<ax::UVSphereComponent>(light, 0.2f, 20, 20).setMaterial(m);

        ax::Entity& cube = ax::Engine::world().entity.create();
        m_cubeTransform = &cube.addComponent<ax::TransformComponent>();
        m_cubeTransform->setTranslation(ax::Vector3f(0.0f, 1.5f, 0.0f));
        cube.addComponent<ax::UVSphereComponent>(cube, 1.0f, 100, 100, true, 8.0f);

        ax::Entity& directionalLight = ax::Engine::world().entity.create();
        directionalLight.addComponent<ax::TransformComponent>().rotate(ax::radians(45.0f), ax::Vector3f(1.0f, 0.0f, 0.0f));
        //directionalLight.addComponent<ax::DirectionalLightComponent>(directionalLight);

        ax::Entity& monkey = ax::Engine::world().entity.create();
        monkey.addComponent<ax::TransformComponent>().setTranslation(10.0f, 3.0f, 0.0f);
        monkey.addComponent<ax::ModelComponent>(monkey).setModel("model_monkey");

        ax::Entity& bunny = ax::Engine::world().entity.create();
        bunny.addComponent<ax::TransformComponent>().setTranslation(14.0f, 2.0f, 0.0f);
        bunny.addComponent<ax::ModelComponent>(bunny).setModel("model_bunny");
    }

    void onUpdate() override
    {
        float delta = ax::Engine::context().getDeltaTime().asSeconds();
        m_time += delta;

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
            ax::Entity& light = ax::Engine::world().entity.create();
            light.addComponent<ax::TransformComponent>().setTranslation(m_spawn->getTranslation() + m_spawn->getForwardVector());
            light.addComponent<ax::PointLightComponent>(light).setRadius(5);
            light.addComponent<ax::UVSphereComponent>(light, 0.2f, 20, 20).setMaterial("light_emission_material"); 
        }

        ax::Vector3f lightPos;
        lightPos.x = std::cos(m_time * 0.5f) * 2.0f;
        lightPos.z = std::sin(m_time * 0.5f) * 2.0f;
        lightPos.y = 0.5f;
        m_lightTransform->setTranslation(lightPos);

        //m_cubeTransform->rotate(delta * 0.3f, ax::Vector3f::up);
        m_cubeTransform->rotate(delta * 0.3f, ax::Vector3f::forward);
    }

private:
    std::vector<ax::TransformComponent*> m_pointlights;
    int MAX_X = 10;
    int MAX_Y = 10;

    ax::TransformComponent* m_spawn;
    ax::Button* spawnButton;

    ax::TransformComponent* m_lightTransform;
    ax::TransformComponent* m_cubeTransform;
    
    float m_time = 0.0f;
};

const std::string CustomSystem::name = "Custom";