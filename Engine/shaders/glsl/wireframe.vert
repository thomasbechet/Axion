#version $GLSL_VERSION
#if __VERSION__ < 430
	#extension GL_ARB_explicit_uniform_location : require
#endif

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_uv;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in vec3 in_tangent;
layout(location = 4) in vec3 in_color;

layout(location = $MVP_MATRIX_LOCATION) uniform mat4 mvp;

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