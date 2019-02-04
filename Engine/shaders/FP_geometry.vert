#version 420 core

layout(location = 0) in vec3 in_vertex;
layout(location = 1) in vec2 in_uv;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in vec3 in_tangent;
layout(location = 4) in vec3 in_color;

uniform mat4 transform;
uniform mat4 mvp;
uniform mat3 normal_to_view;

out vec2 UV;
out vec3 NORMAL;
out mat3 TBN;

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

	UV = in_uv;

	NORMAL = normalize(normal_to_view * in_normal);

	vec3 N = normalize(mat3(transform) * in_normal);
	vec3 T = normalize(mat3(transform) * in_tangent);
	vec3 B = cross(T, N);
	TBN = mat3(camera_view) * mat3(T, B, N);
}