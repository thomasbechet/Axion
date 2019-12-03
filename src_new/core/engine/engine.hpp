#pragma once

namespace ax
{
    template<typename starter>
    class engine
    {
    public:
        engine() noexcept
        {

        }

        void start() noexcept
        {
            id entity = entities.create();
            entities.destroy(entity);
        }

    private:
        component_manager m_component_manager;
        entity_manager m_entity_manager;
    };
}