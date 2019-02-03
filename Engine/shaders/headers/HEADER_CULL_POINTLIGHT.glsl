layout(packed, binding = POINTLIGHT_CULL_SSBO_BINDING_POINT) readonly buffer PointLightsCullIndices
{
    int point_lights_cull_indices[];
};

uint getCullID()
{
    vec2 stride = textureSize(gbuffer_depth_texture, 0).xy / CULL_TILE_SIZE;
    ivec2 tileID = ivec2(floor(gl_FragCoord.xy / stride));
    return tileID.y * CULL_TILE_SIZE + tileID.x;

    //ivec2 tileID = floor(gl_FragCoord.xy / float(CULL_TILE_SIZE));
    //return tileID.y * (screenSize.x / CULL_TILE_SIZE) + tileID.x;
}

bool isPointLightCullIndexValid(uint offset, uint index)
{
    return (index < POINTLIGHT_CULL_MAX_NUMBER) && (point_lights_cull_indices[offset + index] != -1);
}
uint getPointLightCullIndex(uint offset, uint index)
{
    return point_lights_cull_indices[offset + index];
}