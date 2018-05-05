#include <Core/Utility/Color.hpp>

using namespace ax;

Color::Color(){}
Color::Color(int gray)
{
    float color = (float)gray / 255.0f;
    r = color;
    g = color;
    b = color;
}
Color::Color(float gray) : r(gray), g(gray), b(gray){}
Color::Color(int _r, int _g, int _b, int _a)
{
    r = (float)_r / 255.0f;
    g = (float)_g / 255.0f;
    b = (float)_b / 255.0f;
    a = (float)_a / 255.0f;
}
Color::Color(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a){}
Color::Color(const Vector4f& vec)
{
    r = vec.x;
    g = vec.y;
    b = vec.z;
    a = vec.w;
}

Color Color::operator*(const Color& color)
{
    return Color(
        r * color.r,
        g * color.g,
        b * color.b,
        a * color.a
    );
}
Color Color::operator*(float k)
{
    return Color(
        r * k,
        g * k,
        b * k,
        a * k
    );
}
Color Color::operator/(const Color& color)
{
    return Color(
        r / color.r,
        g / color.g,
        b / color.b,
        a / color.a
    );
}
Color Color::operator+(const Color& color)
{
    return Color(
        r + color.r,
        g + color.g,
        b + color.b,
        a + color.a
    );
}
Color Color::operator-(const Color& color)
{
    return Color(
        r - color.r,
        g - color.g,
        b - color.b,
        a - color.a
    );
}

Vector4f Color::toVector() const noexcept
{
    return Vector4f((float)r, (float)g, (float)b, (float)a);
}

Color Color::decode(unsigned raw) noexcept
{
    return Color(
        (int)(raw & 0xFF000000),
        (int)(raw & 0x00FF0000),
        (int)(raw & 0x0000FF00),
        (int)(raw & 0x000000FF)
    );
}
unsigned Color::encode(const Color& color) noexcept
{
    return (unsigned)(color.r * 255.0f) << 24
    | (unsigned)(color.g * 255.0f) << 16
    | (unsigned)(color.b * 255.0f) << 8
    | (unsigned)(color.a * 255.0f);
}