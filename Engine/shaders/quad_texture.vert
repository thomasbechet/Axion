#version 420 core

layout(location = 0) in vec2 in_vertex;

#include HEADER_CAMERA

out vec2 UV;

void main()
{
	gl_Position = vec4(in_vertex, 0.0f, 1.0f);
	UV = in_vertex.xy * 0.5f + 0.5f;
}