#pragma once

/////////////
//HEADERS
/////////////
#include <Core/Export.hpp>
#include <Core/Math/Vector.hpp>
#include <Core/Math/Quaternion.hpp>
#include <Core/Math/Matrix.hpp>

#include <string>

namespace ax
{
    struct AXION_CORE_API Transform2D
    {
        Transform2D(
            Vector2f translation = Vector2f(0.0f, 0.0f), 
            float rotation = 0.0f, 
            Vector2f scale = Vector2f(1.0f, 1.0f)
        );
        ~Transform2D();

        void setTranslation(float x = 0.0f, float y = 0.0f) noexcept;
        void setTranslation(const Vector2f& translation) noexcept;
        Vector2f getTranslation() const noexcept;
        void setRotation(float rotation) noexcept;
        float getRotation() const noexcept;
        void setScale(float x = 1.0f, float y = 1.0f) noexcept;
        void setScale(const Vector2f& scale) noexcept;
        Vector2f getScale() const noexcept;

        void rotate(float rotation) noexcept;
        void translate(Vector2f vec) noexcept;

        void attachTo(Transform2D& newParent) noexcept;
        void detach() noexcept;
        bool isAttached() const noexcept;
        bool hasChild() const noexcept;

        Matrix3f getWorldMatrix() noexcept;
        Matrix3f getMatrix() noexcept;

    protected:
        void setParent(Transform2D* newParent) noexcept;
        Matrix3f localToWorld() noexcept;
        Matrix3f localToParent() noexcept;

        Vector2f m_translation = Vector2f(0.0f, 0.0f);
        float m_rotation = 0.0f;
        Vector2f m_scale = Vector2f(1.0f, 1.0f);
 
        Matrix3f m_transform;
        bool m_requestCompute = true;

        Transform2D* parent = nullptr;
        Transform2D* firstChild = nullptr;
        Transform2D* nextSibling = nullptr;
        Transform2D* prevSibling = nullptr;
    };
}