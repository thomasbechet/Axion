#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/Math/Vector.hpp>
#include <Core/Math/Matrix.hpp>
#include <Core/Math/Quaternion.hpp>

namespace ax
{
    class AXION_CORE_API Transform
    {
    public:
        const Vector3f& getTranslation() const noexcept;
        void setTranslation(const Vector3f& translation) noexcept;
        void setTranslation(float x, float y, float z) noexcept;
        void translate(const Vector3f& translate) noexcept;
        void translate(float x, float y, float z) noexcept;

        const Quaternionf& getRotation() const noexcept;
        void setRotation(const Quaternionf& rotation) noexcept;
        
        const Vector3f& getScale() const noexcept;
        void setScale(const Vector3f& scale) noexcept;

        Matrix4f matrix() noexcept;

    private:
        void computeMatrix() noexcept;

    private:
        Vector3f m_translation = Vector3f(0.0f, 0.0f, 0.0f);
        Quaternionf m_rotation = Quaternionf(0.0f, Vector3f(0.0f, 1.0f, 0.0f));
        Vector3f m_scale = Vector3f(1.0f, 1.0f, 1.0f);
        Matrix4f m_transform;
        bool m_computeRequest = true;
    };
}