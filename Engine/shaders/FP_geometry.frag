#version 420 core

layout(early_fragment_tests) in;
layout(location = 0) out vec3 out_normal;

in vec2 UV;
in vec3 NORMAL;
in mat3 TBN;

#include HEADER_MATERIAL

void main()
{
	out_normal = getNormal();
}