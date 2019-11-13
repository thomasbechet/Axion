#pragma once

#include <Core/Export.hpp>
#include <Core/Math/Vector.hpp>

namespace ax
{
    class AXION_CORE_API Color3
    {
    public:
        Color3();
        Color3(int gray);
        Color3(float gray);
        Color3(int _r, int _g, int _b);
        Color3(float _r, float _g, float _b);
        Color3(const Vector3f& vec);
        Color3(const Json& json);

        Color3 operator*(const Color3& color);
        Color3 operator*(float k);
        Color3 operator/(const Color3& color);
        Color3 operator+(const Color3& color);
        Color3 operator-(const Color3& color);

        Vector3f toVector() const noexcept;

    public:
        float r = 1.0f;
        float g = 1.0f;
        float b = 1.0f;
    };

    class AXION_CORE_API Color4
    {
    public:
        Color4();
        Color4(int gray);
        Color4(float gray);
        Color4(int _r, int _g, int _b, int _a = 255);
        Color4(float _r, float _g, float _b, float _a = 1.0f);
        Color4(const Vector4f& vec);
        Color4(const Json& json);

        Color4 operator*(const Color4& color);
        Color4 operator*(float k);
        Color4 operator/(const Color4& color);
        Color4 operator+(const Color4& color);
        Color4 operator-(const Color4& color);

        Vector4f toVector() const noexcept;

        static Color4 decode(unsigned raw) noexcept;
        static unsigned encode(const Color4& color) noexcept;

    public:
        float r = 1.0f;
        float g = 1.0f;
        float b = 1.0f;
        float a = 1.0f;
    };
}