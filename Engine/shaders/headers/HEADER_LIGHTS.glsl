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
    vec2 stride = textureSize(gbuffer_depth_texture, 0).xy / SGC_CULL_TILE_SIZE;
    ivec2 tileID = ivec2(floor(gl_FragCoord.xy / stride));
    return tileID.y * SGC_CULL_TILE_SIZE + tileID.x;

    //ivec2 tileID = floor(gl_FragCoord.xy / float(CULL_TILE_SIZE));
    //return tileID.y * (screenSize.x / CULL_TILE_SIZE) + tileID.x;
}
bool isPointLightCullIndexValid(uint offset, uint index)
{
    return (index < SGC_POINTLIGHT_CULL_MAX_NUMBER) && (point_lights_cull_indices[offset + index] != -1);
}
uint getPointLightCullIndex(uint offset, uint index)
{
    return point_lights_cull_indices[offset + index];
}