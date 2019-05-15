#version $GLSL_VERSION
#if __VERSION__ < 430
	#extension GL_ARB_explicit_uniform_location : require
#endif

out vec4 out_color;

in vec2 UV;

layout(binding = $GUI_TEXTURE_BINDING) uniform sampler2D gui_texture;
layout(location = $GUI_COLOR_LOCATION) uniform vec4 gui_color;

//CONSTANTS//
struct Constant
{
    uvec2 viewportResolution;
	uvec2 windowSize;
};
layout(std140, binding = $CONSTANTS_UBO_BINDING_POINT) uniform Constants
{
    Constant constants;
};

void main()
{
	out_color = texture(gui_texture, UV).rgba * gui_color;
}