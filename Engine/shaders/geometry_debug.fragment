#version 420 core

layout(binding = 0) uniform sampler2D gbuffer_albedo;
layout(binding = 1) uniform sampler2D gbuffer_normal;
layout(binding = 2) uniform sampler2D gbuffer_position;
layout(binding = 3) uniform sampler2D gbuffer_depth;

in vec2 UV;
out vec4 out_color;

#define ZNEAR 0.01
#define ZFAR 100.0

#define USE_CAMERA_UNIFORM_BLOCK 1
#if USE_CAMERA_UNIFORM_BLOCK

	#define CAMERA_BINDING_POINT 3

	layout(std140, binding = CAMERA_BINDING_POINT) uniform Camera
	{
		mat4 camera_view;
		mat4 camera_projection;
		mat4 inv_camera_view;
		mat4 inv_camera_projection;
	};

#endif

vec3 viewPosFromDepth(float depth)
{
    float z = depth * 2.0 - 1.0;

    vec4 clipSpacePosition = vec4(UV * 2.0 - 1.0, z, 1.0);
    vec4 viewSpacePosition = inv_camera_projection * clipSpacePosition;

    //Perspective division
    viewSpacePosition /= viewSpacePosition.w;

    return viewSpacePosition.xyz;
}

vec4 albedo(in vec2 uv)
{
	return vec4(texture2D(gbuffer_albedo, uv).xyz, 1.0f);
}
vec4 normal(in vec2 uv)
{
	return vec4(texture2D(gbuffer_normal, uv).rgb * 0.5 + 0.5, 1.0f);
}
vec4 position(in vec2 uv)
{
	vec3 fragPos = vec3(gl_FragCoord.x, gl_FragCoord.y, 0.0f);
	fragPos.z = texture(gbuffer_depth, UV).x * 2.0f - 1.0f;
	return vec4(fragPos, 1.0f);
}
vec4 depth(in vec2 uv)
{
	float depth = texture2D(gbuffer_depth, uv).x;
	return vec4((2.0 * ZNEAR) / (ZFAR + ZNEAR - depth * (ZFAR - ZNEAR)));
}

void main()
{
	out_color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	
	if(UV.x < 0.5)
		if(UV.y < 0.5)
			out_color = position(UV * 2.0);
		else
			out_color = albedo(vec2(UV.x * 2.0, (UV.y - 0.5) * 2.0));
	else
		if(UV.y < 0.5)
			out_color = depth(vec2((UV.x - 0.5) * 2.0, UV.y * 2.0));
		else
			out_color = normal((UV - 0.5) * 2.0);
}