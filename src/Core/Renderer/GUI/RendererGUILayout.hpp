#pragma once

#include <Core/Export.hpp>
#include <Core/Renderer/GUI/RendererGUIRectangle.hpp>
#include <Core/Renderer/GUI/RendererGUIScalableRectangle.hpp>

namespace ax
{
    class AXION_CORE_API RendererGUILayout
    {
    public:
        virtual RendererGUIRectangleHandle createRectangle() = 0;
        virtual void destroyRectangle(RendererGUIRectangleHandle& handle) = 0;

        virtual RendererGUIScalableRectangleHandle createScalableRectangle() = 0;
        virtual void destroyScalableRectangle(RendererGUIScalableRectangleHandle& handle) = 0;
    };

    class AXION_CORE_API NullRendererGUILayout : public RendererGUILayout
    {
    public:
        RendererGUIRectangleHandle createRectangle() override {return &m_nullRectangle;}
        void destroyRectangle(RendererGUIRectangleHandle& handle) override {handle = nullptr;}

        RendererGUIScalableRectangleHandle createScalableRectangle() override {return &m_nullScalableRectangle;}
        void destroyScalableRectangle(RendererGUIScalableRectangleHandle& handle) override {handle = nullptr;}

    private:
        NullRendererGUIRectangle m_nullRectangle; 
        NullRendererGUIScalableRectangle m_nullScalableRectangle; 
    };

    using RendererGUILayoutHandle = RendererGUILayout*;
}