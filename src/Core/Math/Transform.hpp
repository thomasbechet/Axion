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
    struct AXION_CORE_API Transform
    {
        Transform(
            Vector3f position = Vector3f(0.0f, 0.0f, 0.0f), 
            Quaternionf rotation = Quaternionf(), 
            Vector3f scale = Vector3f(1.0f, 1.0f, 1.0f)
        );
        ~Transform();

        void setTranslation(float x = 0.0f, float y = 0.0f, float z = 0.0f) noexcept;
        void setTranslation(const Vector3f& position) noexcept;
        Vector3f getTranslation() noexcept;
        void setRotation(float angle = 0.0f, const Vector3f& axis = Vector3f(0.0f, 1.0f, 0.0f)) noexcept;
        void setRotation(const Quaternionf& rotation) noexcept;
        Quaternionf getRotation() noexcept;
        void setScale(float x = 1.0f, float y = 1.0f, float z = 1.0f) noexcept;
        void setScale(const Vector3f& scale) noexcept;
        Vector3f getScale() noexcept;

        void rotate(float angle, Vector3f axis) noexcept;
        void translate(Vector3f vec) noexcept;

        Vector3f getForwardVector() noexcept;
        Vector3f getBackwardVector() noexcept;
        Vector3f getLeftVector() noexcept;
        Vector3f getRightVector() noexcept;
        Vector3f getUpVector() noexcept;
        Vector3f getDownVector() noexcept;

        void attachTo(Transform& newParent) noexcept;
        void detach() noexcept;
        bool isAttached() const noexcept;
        bool hasChild() const noexcept;

        Matrix4f getWorldMatrix() noexcept;
        Matrix4f getMatrix() noexcept;

    protected:
        void setParent(Transform* newParent) noexcept;
        Matrix4f localToWorld() noexcept;
        Matrix4f localToParent() noexcept;

        Vector3f m_translation = Vector3f(0.0f, 0.0f, 0.0f);
        Quaternionf m_rotation = Quaternionf(0.0f, Vector3f(0.0f, 1.0f, 0.0f));
        Vector3f m_scale = Vector3f(1.0f, 1.0f, 1.0f);
 
        Matrix4f m_transform;
        bool m_requestCompute = true;

        Transform* parent = nullptr;
        Transform* firstChild = nullptr;
        Transform* nextSibling = nullptr;
        Transform* prevSibling = nullptr;
    };
}