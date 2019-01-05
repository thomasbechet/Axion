#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/Math/Vector.hpp>

namespace ax
{
    class AXION_CORE_API Color3
    {
    public:
        Color3(){}
        Color3(int gray)
        {
            float color = (float)gray / 255.0f;
            r = color;
            g = color;
            b = color;
        }
        Color3(float gray)
        {
            r = gray;
            g = gray;
            b = gray;
        }
        Color3(int _r, int _g, int _b)
        {
            r = (float)_r / 255.0f;
            g = (float)_g / 255.0f;
            b = (float)_b / 255.0f;
        }
        Color3(float _r, float _g, float _b)
        {
            r = _r;
            g = _g;
            b = _b;
        }
        Color3(const Vector3f& vec)
        {
            r = vec.x;
            g = vec.y;
            b = vec.z;
        }

        Color3 operator*(const Color3& color)
        {
            return Color3(
                r * color.r,
                g * color.g,
                b * color.b
            );
        }
        Color3 operator*(float k)
        {
            return Color3(
                r * k,
                g * k,
                b * k
            );
        }
        Color3 operator/(const Color3& color)
        {
            return Color3(
                r / color.r,
                g / color.g,
                b / color.b
            );
        }
        Color3 operator+(const Color3& color)
        {
            return Color3(
                r + color.r,
                g + color.g,
                b + color.b
            );
        }
        Color3 operator-(const Color3& color)
        {
            return Color3(
                r - color.r,
                g - color.g,
                b - color.b
            );
        }

        Vector3f toVector() const noexcept
        {
            return Vector3f((float)r, (float)g, (float)b);
        }

    public:
        float r = 1.0f;
        float g = 1.0f;
        float b = 1.0f;
    };

    class AXION_CORE_API Color4
    {
    public:
        Color4(){}
        Color4(int gray)
        {
            float color = (float)gray / 255.0f;
            r = color;
            g = color;
            b = color;
        }
        Color4(float gray)
        {
            r = gray;
            g = gray;
            b = gray;
            a = gray;
        }
        Color4(int _r, int _g, int _b, int _a = 255)
        {
            r = (float)_r / 255.0f;
            g = (float)_g / 255.0f;
            b = (float)_b / 255.0f;
            a = (float)_a / 255.0f;
        }
        Color4(float _r, float _g, float _b, float _a = 1.0f)
        {
            r = _r;
            g = _g;
            b = _b;
            a = _a;
        }
        Color4(const Vector4f& vec)
        {
            r = vec.x;
            g = vec.y;
            b = vec.z;
            a = vec.w;
        }

        Color4 operator*(const Color4& color)
        {
            return Color4(
                r * color.r,
                g * color.g,
                b * color.b,
                a * color.a
            );
        }
        Color4 operator*(float k)
        {
            return Color4(
                r * k,
                g * k,
                b * k,
                a * k
            );
        }
        Color4 operator/(const Color4& color)
        {
            return Color4(
                r / color.r,
                g / color.g,
                b / color.b,
                a / color.a
            );
        }
        Color4 operator+(const Color4& color)
        {
            return Color4(
                r + color.r,
                g + color.g,
                b + color.b,
                a + color.a
            );
        }
        Color4 operator-(const Color4& color)
        {
            return Color4(
                r - color.r,
                g - color.g,
                b - color.b,
                a - color.a
            );
        }

        Vector4f toVector() const noexcept
        {
            return Vector4f((float)r, (float)g, (float)b, (float)a);
        }

        static Color4 decode(unsigned raw) noexcept
        {
            return Color4(
                (int)(raw & 0xFF000000),
                (int)(raw & 0x00FF0000),
                (int)(raw & 0x0000FF00),
                (int)(raw & 0x000000FF)
            );
        }
        static unsigned encode(const Color4& color) noexcept
        {
            return (unsigned)(color.r * 255.0f) << 24
            | (unsigned)(color.g * 255.0f) << 16
            | (unsigned)(color.b * 255.0f) << 8
            | (unsigned)(color.a * 255.0f);
        }

    public:
        float r = 1.0f;
        float g = 1.0f;
        float b = 1.0f;
        float a = 1.0f;
    };
}