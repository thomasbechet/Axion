#pragma once

#include <Core/Export.hpp>
#include <Core/GUI/GUILayout.hpp>
#include <Core/GUI/Widget/GUIButton.hpp>
#include <Core/GUI/Widget/GUIText.hpp>
#include <Core/Utility/IndexVector.hpp>

namespace ax
{
    class AXION_CORE_API GUI
    {
    public:
        static constexpr const Id DefaultLayout = 1;

    public:
        virtual ~GUI() = default;

    public:
        virtual void initialize() noexcept = 0;
        virtual void terminate() noexcept = 0;
        virtual void update() noexcept = 0;
        virtual void render() noexcept = 0;

        virtual Id createLayout() noexcept = 0;
        virtual void destroyLayout(Id layout) noexcept = 0;

        virtual Id createButton(Id layout) noexcept = 0;
        virtual void destroyButton(Id button) noexcept = 0;
        virtual Id createText(Id layout) noexcept = 0;
        virtual void destroyText(Id button) noexcept = 0;

    protected:
        template<typename T>
        Id addLayout() noexcept
        {
            return m_layouts.add(std::make_unique<GUILayout>());
        }
        template<typename T>
        T& getLayout(Id id) noexcept
        {
            return static_cast<T&>(*m_layouts.get(id).get());
        }
        void removeLayout(Id layout) noexcept
        {
            m_layouts.remove(layout);
        }

        IndexVector<std::unique_ptr<GUILayout>> m_layouts;        
    };
}