#version 430 core

layout(location = 0) in vec3 in_position;

//layout(location = $MVP_MATRIX_LOCATION) uniform mat4 mvp;

layout(location = $TRANSFORM_MATRIX_LOCATION) uniform mat4 transform;
layout(location = $MVP_MATRIX_LOCATION) uniform mat4 mvp;
layout(location = $NORMALTOVIEW_MATRIX_LOCATION) uniform mat3 normal_to_view;

layout(std140, binding = $CAMERA_UBO_BINDING_POINT) uniform Camera
{
    mat4 camera_projection;
    mat4 camera_view;
    mat4 inv_camera_projection;
};

void main()
{
	gl_Position = mvp * vec4(in_position, 1.0f);
}