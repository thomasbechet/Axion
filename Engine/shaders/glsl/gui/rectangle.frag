#version 430 core

out vec4 out_color;

in vec2 UV;

layout(binding = $GUI_TEXTURE_BINDING) uniform sampler2D gui_texture;

void main()
{
	out_color = texture(gui_texture, UV).rgba;
}