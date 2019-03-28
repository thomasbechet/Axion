#pragma once

#include <Core/Export.hpp>
#include <Core/Math/Geometry/Shape.hpp>
#include <Core/Math/Geometry/Sphere.hpp>

namespace ax
{
    class AXION_CORE_API IcoSphere : public Shape, public Sphere
    {
    public:
        IcoSphere(float radius);

    private:
        
    };
}