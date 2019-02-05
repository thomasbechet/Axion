struct DirectionalLight
{
    vec3 direction;
    float pad;
    vec3 color;
    float intensity;
};
layout(std140, binding = SGC_DIRECTIONALLIGHT_UBO_BINDING_POINT) uniform DirectionalLights
{
    DirectionalLight directional_lights[SGC_DIRECTIONALLIGHT_MAX_NUMBER];
    uint directional_lights_count;
};

struct PointLight
{
    vec3 position;
    float radius;
    vec3 color;
    float intensity;
};
layout(std140, binding = SGC_POINTLIGHT_UBO_BINDING_POINT) uniform PointLights
{ 
    PointLight point_lights[SGC_POINTLIGHT_MAX_NUMBER];
    uint point_light_count;
};

layout(packed, binding = SGC_POINTLIGHT_CULL_SSBO_BINDING_POINT) readonly buffer PointLightsCullIndices
{
    int point_lights_cull_indices[];
};

uint getCullID()
{
    ivec2 tileID = ivec2(floor(gl_FragCoord.xy / float(SGC_CULL_TILE_SIZE)));
    return tileID.y * (shader_constants.resolution.x / SGC_CULL_TILE_SIZE) + tileID.x;
}
bool isPointLightCullIndexValid(uint offset, uint index)
{
    return (index < SGC_POINTLIGHT_CULL_MAX_NUMBER) && (point_lights_cull_indices[offset + index] != -1);
}
uint getPointLightCullIndex(uint offset, uint index)
{
    return point_lights_cull_indices[offset + index];
}