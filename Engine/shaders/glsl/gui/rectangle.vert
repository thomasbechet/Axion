#version 430 core

layout(location = 0) in vec2 in_position;
layout(location = 1) in vec2 in_uv;

out vec2 UV;

layout(location = $TRANSFORM_MATRIX_LOCATION) uniform mat3 transform;
layout(location = $LAYOUT_SIZE_LOCATION) uniform vec2 layout_size;

void main()
{
	UV = in_uv;
	vec2 vpos = (transform * vec3(in_position, 1.0f)).xy;
	gl_Position = vec4((2.0f * vpos.xy) / layout_size.xy - 1.0f, 0.0f, 1.0f);
}