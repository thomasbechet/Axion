#version 430 core

layout(location = 0) in vec3 in_vertex;
layout(location = 1) in vec2 in_uv;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in vec3 in_tangent;
layout(location = 4) in vec3 in_color;

layout(location = 0) uniform mat4 mvp;

#include GLOBAL_CONSTANTS

layout(std140, binding = SGC_CAMERA_UBO_BINDING_POINT) uniform Camera
{
    mat4 camera_projection;
    mat4 camera_view;
    mat4 inv_camera_projection;
};

void main()
{
	gl_Position = mvp * vec4(in_vertex, 1.0f);
}