#pragma once

namespace ax
{
    //CONSTANTS//
    constexpr auto MATERIAL_UBO_BINDING_POINT = 1;
    constexpr auto MATERIAL_MAX_NUMBER = 50;
    constexpr auto MATERIAL_USE_DIFFUSE_TEXTURE = 1;
    constexpr auto MATERIAL_USE_DIFFUSE_COLOR = 2;
    constexpr auto MATERIAL_USE_NORMAL_TEXTURE = 4;
    constexpr auto MATERIAL_IS_BUMP_TEXTURE = 8;
    constexpr auto MATERIAL_USE_SPECULAR_TEXTURE = 16;

    constexpr auto CAMERA_UBO_BINDING_POINT = 2;

    constexpr auto POINT_LIGHT_UBO_BINDING_POINT = 3;
    constexpr auto POINT_LIGHT_MAX_NUMBER = 500;

    constexpr auto DIRECTIONAL_LIGHT_UBO_BINDING_POINT = 4;
    constexpr auto DIRECTIONAL_LIGHT_MAX_NUMBER = 50;

    constexpr auto USE_LIGHT_CULLING = true;
    constexpr auto CULL_POINT_LIGHT_SSBO_BINDING_POINT = 1;
    constexpr auto CULL_POINT_LIGHT_MAX_PER_TILE = 512;
    constexpr auto CULL_TILE_SIZE = 32;

    constexpr auto CONSTANTS_UBO_BINDING_POINT = 6;

    //LOCATIONS AND BINDINGS//
    constexpr auto MATERIAL_INDEX_LOCATION = 0;
    constexpr auto MVP_MATRIX_LOCATION = 1;
    constexpr auto TRANSFORM_MATRIX_LOCATION = 2;
    constexpr auto NORMALTOVIEW_MATRIX_LOCATION = 3;
    constexpr auto GUI_COLOR_LOCATION = 4;

    constexpr auto DIFFUSE_TEXTURE_BINDING = 0;
    constexpr auto NORMAL_TEXTURE_BINDING = 1;
    constexpr auto SPECULAR_TEXTURE_BINDING = 2; 
    constexpr auto GUI_TEXTURE_BINDING = 3;

    constexpr auto GBUFFER_NORMAL_TEXTURE_BINDING = 3;
    constexpr auto GBUFFER_DEPTH_TEXTURE_BINDING = 4;

    //GLSL VERSION
    constexpr auto GLSL_VERSION = USE_LIGHT_CULLING ? "430 core" : "420 core";
}