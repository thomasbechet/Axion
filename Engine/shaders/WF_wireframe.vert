#version 420 core

layout(location = 0) in vec3 in_vertex;
layout(location = 1) in vec2 in_uv;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in vec3 in_tangent;
layout(location = 4) in vec3 in_color;

uniform mat4 mvp;

#define USE_CAMERA_UNIFORM_BLOCK 1
#if USE_CAMERA_UNIFORM_BLOCK

	#define CAMERA_BINDING_POINT 2

	layout(std140, binding = CAMERA_BINDING_POINT) uniform Camera
	{
		mat4 camera_view;
		mat4 inv_camera_projection;
	};

#endif

void main()
{
	gl_Position = mvp * vec4(in_vertex, 1.0f);
}