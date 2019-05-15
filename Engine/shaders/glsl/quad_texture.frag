#version $GLSL_VERSION

layout(location = 0) out vec3 out_color;

layout(binding = 0) uniform sampler2D render_texture;

in vec2 UV;

void main()
{
	out_color = texture2D(render_texture, UV).xyz;
}