#version 420 core

out vec3 out_color;

uniform sampler2D render_texture;

in vec2 UV;

void main()
{
	out_color = texture2D(render_texture, UV).xyz;
}