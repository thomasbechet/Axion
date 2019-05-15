#version $GLSL_VERSION
#if __VERSION__ < 430
	#extension GL_ARB_explicit_uniform_location : require
#endif

layout(location = 0) in vec2 in_position;
layout(location = 1) in vec2 in_uv;

out vec2 UV;

layout(location = $TRANSFORM_MATRIX_LOCATION) uniform mat3 transform;

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
	UV = in_uv;
	vec2 vpos = (transform * vec3(in_position, 1.0f)).xy;
	gl_Position = vec4((2.0f * vpos.xy) / constants.windowSize.xy - 1.0f, 0.0f, 1.0f);
}