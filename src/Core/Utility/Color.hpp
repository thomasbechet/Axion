#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/Math/Vector.hpp>

namespace ax
{
    class AXION_CORE_API Color
    {
    public:
        Color();
        Color(int gray); //Grayscale
        Color(float gray); //Grayscale
        Color(int r, int g, int b, int a = 255);
        Color(float r, float g, float b, float a = 1.0f);
        Color(const Vector4f& vec);

        Color operator*(const Color& color);
        Color operator*(float k);
        Color operator/(const Color& color);
        Color operator+(const Color& color);
        Color operator-(const Color& color);

        Vector4f toVector() const noexcept;

        static Color decode(unsigned raw) noexcept;
        static unsigned encode(const Color& color) noexcept;

    public:
        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
        float a = 1.0f;
    };
}