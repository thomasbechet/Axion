#pragma once

#include <Core/Export.hpp>

namespace ax
{
    struct AXION_CORE_API RendererCameraParameters
    {
        float fov = 90.0f;
        float near = 0.01f;
        float far = 100.0f;
    };
}