#version 430 core

out vec3 out_color;

layout(binding = 0) uniform sampler2D render_texture;

in vec2 UV;

///////////////////////////
///////////////////////////

//CONSTANTS//
struct Constant
{
    uvec2 viewportResolution;
	uvec2 windowSize;
};
layout(std140, binding = $CONSTANTS_UBO_BINDING_POINT) uniform Constants
{
    Constant constants;
};

//POINT LIGHTS//
struct PointLight 
{
    vec3 position;
    float radius;
    vec3 color;
    float intensity;
};
layout(std140, binding = $POINT_LIGHT_UBO_BINDING_POINT) uniform PointLights
{ 
    PointLight point_lights[$POINT_LIGHT_MAX_NUMBER];
    uint point_light_count;
};

#if ($USE_LIGHT_CULLING == 1)
    layout(packed, binding = $CULL_POINT_LIGHT_SSBO_BINDING_POINT) readonly buffer PointLightsCullIndices
    {
        int point_lights_cull_indices[];
    };

    uint getCullKey()
    {
        ivec2 tileID = ivec2(gl_FragCoord.xy) / $CULL_TILE_SIZE;
        return (tileID.y * (constants.viewportResolution.x / $CULL_TILE_SIZE) + tileID.x) * $CULL_POINT_LIGHT_MAX_PER_TILE;
    }
    PointLight getCullPointLight(uint index, uint cullKey)
    {
        return point_lights[point_lights_cull_indices[cullKey + index + 1]];
    }
    uint getCullPointLightCount(uint cullKey)
    {
        return point_lights_cull_indices[cullKey];
    }
#else
    uint getPointLightCount()
    {
        return point_light_count;
    }
    PointLight getPointLight(uint index)
    {
        return point_lights[index];
    }
#endif

//DIRECTIONAL LIGHTS//
struct DirectionalLight
{
    vec3 direction;
    float pad;
    vec3 color;
    float intensity;
};
layout(std140, binding = $DIRECTIONAL_LIGHT_UBO_BINDING_POINT) uniform DirectionalLights
{
    DirectionalLight directional_lights[$DIRECTIONAL_LIGHT_MAX_NUMBER];
    uint directional_lights_count;
};

uint getDirectionalLightCount()
{
    return directional_lights_count;
}
DirectionalLight getDirectionalLight(uint index)
{
    return directional_lights[index];
}

void main()
{
	vec3 color = vec3(0.0f, 0.0f, 1.0f);

    #if ($USE_LIGHT_CULLING == 1)
		uint cullKey = getCullKey();
		uint count = getCullPointLightCount(cullKey);
	#else
        uint count = 0;
	#endif

	float I = float(count) / 64.0f;

    if(I > 0.0f)
    {
        vec3 start = vec3(0.0f, 1.0f, 0.0f);
        vec3 end = vec3(1.0f, 0.0f, 0.0f);
        color = mix(start, end, I);
    }

    vec3 image = texture2D(render_texture, UV).xyz;

	out_color = image * 0.5 + color * 0.5;

    if(int(gl_FragCoord.x) % $CULL_TILE_SIZE == 0 || int(gl_FragCoord.y) % $CULL_TILE_SIZE == 0)
    {
        out_color = vec3(0, 0, 0);
    }
}   