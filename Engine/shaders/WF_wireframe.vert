#version 430 core

layout(location = 0) in vec3 in_vertex;
layout(location = 1) in vec2 in_uv;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in vec3 in_tangent;
layout(location = 4) in vec3 in_color;

layout(location = 0) uniform mat4 mvp;

#include HEADER_CAMERA

void main()
{
	gl_Position = mvp * vec4(in_vertex, 1.0f);
}