#version 430 core

layout(location = 0) out vec3 out_color;

void main()
{
	const float intensity = 50.0f;
	out_color = vec3(intensity);
}