#version 430 core

out vec4 out_color;

in vec2 UV;

layout(binding = 0) uniform sampler2D gui_background;
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

uniform float offset[5] = float[](0.0, 1.0, 2.0, 3.0, 4.0);
uniform float weight[5] = float[](0.2270270270, 0.1945945946, 0.1216216216,
                                  0.0540540541, 0.0162162162);

void main()
{
	vec4 out_color = texture2D(gui_background, vec2(gl_FragCoord) / constants.windowSize) * weight[0];
	for (int i=1; i<5; i++) {
        out_color +=
            texture2D(gui_background, (vec2(gl_FragCoord) + vec2(0.0, offset[i])) / constants.windowSize)
                * weight[i];
        out_color +=
            texture2D(gui_background, (vec2(gl_FragCoord) - vec2(0.0, offset[i])) / constants.windowSize)
                * weight[i];
    }
	out_color.a = 1.0;
	
	out_color = texture(gui_background, gl_FragCoord.xy).rgba * vec4(1.0f, 0.0f, 0.0f, 1.0);
	out_color = gl_FragCoord;

	//out_color = texture(gui_texture, UV).rgba * gui_color.rgba;
}