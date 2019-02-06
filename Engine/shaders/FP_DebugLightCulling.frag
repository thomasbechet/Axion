#version 430 core

out vec3 out_color;

layout(binding = 0) uniform sampler2D render_texture;

in vec2 UV;

///////////////////////////
///////////////////////////

#include GLOBAL_CONSTANTS
#include HEADER_UNIFORMS
#include HEADER_LIGHTS

void main()
{
	vec3 color = vec3(0.0f, 0.0f, 1.0f);

    uint i = 0;
    uint tileID = getCullID();
	uint key = tileID * SGC_POINTLIGHT_CULL_MAX_NUMBER;
    while(isPointLightCullIndexValid(key, i)) i++;

	float I = float(i) / 64.0f;	

    if(I > 0.0f)
    {
        vec3 start = vec3(0.0f, 1.0f, 0.0f);
        vec3 end = vec3(1.0f, 0.0f, 0.0f);
        color = mix(start, end, I);
    }

    vec3 image = texture2D(render_texture, UV).xyz;

	out_color = image * 0.5 + color * 0.5;

    if(int(gl_FragCoord.x) % SGC_CULL_TILE_SIZE == 0 || int(gl_FragCoord.y) % SGC_CULL_TILE_SIZE == 0)
    {
        out_color = vec3(0, 0, 0);
    }
}   