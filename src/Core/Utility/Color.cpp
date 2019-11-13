#include <Core/Utility/Color.hpp>

using namespace ax;

Color4::Color4(){}
Color4::Color4(int gray)
{
    float color = (float)gray / 255.0f;
    r = color;
    g = color;
    b = color;
}
Color4::Color4(float gray)
{
    r = gray;
    g = gray;
    b = gray;
    a = gray;
}
Color4::Color4(int _r, int _g, int _b, int _a = 255)
{
    r = (float)_r / 255.0f;
    g = (float)_g / 255.0f;
    b = (float)_b / 255.0f;
    a = (float)_a / 255.0f;
}
Color4::Color4(float _r, float _g, float _b, float _a = 1.0f)
{
    r = _r;
    g = _g;
    b = _b;
    a = _a;
}
Color4::Color4(const Vector4f& vec)
{
    r = vec.x;
    g = vec.y;
    b = vec.z;
    a = vec.w;
}
Color4::Color4(const Json& json)
{
    try
    {
        if(json.is_array())
        {
            std::vector<float> values = json.get<std::vector<float>>();
            if(values.size() <= 3)
            {
                r = values.at(0) / 255.0f;
                g = values.at(1) / 255.0f;
                b = values.at(2) / 255.0f;
            }
            if(values.size() >= 4)
                a = values.at(3) / 255.0f;
        }   
    }
    catch(...) {}
}

Color4 Color4::operator*(const Color4& color)
{
    return Color4(
        r * color.r,
        g * color.g,
        b * color.b,
        a * color.a
    );
}
Color4 Color4::operator*(float k)
{
    return Color4(
        r * k,
        g * k,
        b * k,
        a * k
    );
}
Color4 Color4::operator/(const Color4& color)
{
    return Color4(
        r / color.r,
        g / color.g,
        b / color.b,
        a / color.a
    );
}
Color4 Color4::operator+(const Color4& color)
{
    return Color4(
        r + color.r,
        g + color.g,
        b + color.b,
        a + color.a
    );
}
Color4 Color4::operator-(const Color4& color)
{
    return Color4(
        r - color.r,
        g - color.g,
        b - color.b,
        a - color.a
    );
}

Vector4f Color4::toVector() const noexcept
{
    return Vector4f((float)r, (float)g, (float)b, (float)a);
}

Color4 Color4::decode(unsigned raw) noexcept
{
    return Color4(
        (int)(raw & 0xFF000000),
        (int)(raw & 0x00FF0000),
        (int)(raw & 0x0000FF00),
        (int)(raw & 0x000000FF)
    );
}
unsigned Color4::encode(const Color4& color) noexcept
{
    return (unsigned)(color.r * 255.0f) << 24
    | (unsigned)(color.g * 255.0f) << 16
    | (unsigned)(color.b * 255.0f) << 8
    | (unsigned)(color.a * 255.0f);
}