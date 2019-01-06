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

    void onUpdate() override
    {
        float delta = ax::Engine::context().getDeltaTime().asSeconds();
        m_time += delta;
        m_transform->rotate(ax::radians(delta * 2.0f), ax::Vector3f(0.0f, 1.0f, 0.0f));
        m_transform->rotate(ax::radians(delta * 5.0f), ax::Vector3f(1.0f, 0.0f, 0.0f));
        //m_transform->setTranslation(ax::Vector3f(0.0f, 3.0f + std::cos(m_time), 0.0f));
    }

private:
    ax::TransformComponent* m_transform;
    float m_time = 0.0f;
};