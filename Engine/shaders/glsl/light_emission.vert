#version 430 core

layout(location = 0) in vec3 in_vertex;

layout(location = $MVP_MATRIX_LOCATION) uniform mat4 mvp;

layout(std140, binding = $CAMERA_UBO_BINDING_POINT) uniform Camera
{
    mat4 camera_projection;
    mat4 camera_view;
    mat4 inv_camera_projection;
};

void main()
{
	gl_Position = mvp * vec4(in_vertex, 1.0f);
}