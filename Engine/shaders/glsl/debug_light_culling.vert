#version $GLSL_VERSION

layout(location = 0) in vec2 in_position;

out vec2 UV;

void main()
{
	gl_Position = vec4(in_position, 0.0f, 1.0f);
	UV = in_position.xy * 0.5f + 0.5f;
}