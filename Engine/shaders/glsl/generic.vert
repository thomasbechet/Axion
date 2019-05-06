#version 430 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_uv;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in vec3 in_tangent;
layout(location = 4) in vec3 in_color;

layout(location = $TRANSFORM_MATRIX_LOCATION) uniform mat4 transform;
layout(location = $MVP_MATRIX_LOCATION) uniform mat4 mvp;
layout(location = $NORMALTOVIEW_MATRIX_LOCATION) uniform mat3 normal_to_view;

out vec2 UV;
out vec3 POSITION;
out vec3 COLOR;
out vec3 NORMAL;
out mat3 TBN;

//CAMERA//
layout(std140, binding = $CAMERA_UBO_BINDING_POINT) uniform Camera
{
    mat4 camera_projection;
    mat4 camera_view;
    mat4 inv_camera_projection;
};

void main()
{
	vec4 position = mvp * vec4(in_position, 1.0f);
	gl_Position = position;

	POSITION = vec3(inv_camera_projection * position);

	UV = in_uv;

	NORMAL = normalize(normal_to_view * in_normal);
	//NORMAL = normalize(mat3(transform) * in_normal);
	//NORMAL = in_normal;

	COLOR = in_color;

	vec3 N = normalize(normal_to_view * in_normal);
	vec3 T = normalize(normal_to_view * in_tangent);
	vec3 B = cross(N, T);
	TBN = transpose(mat3(T, B, N));
}