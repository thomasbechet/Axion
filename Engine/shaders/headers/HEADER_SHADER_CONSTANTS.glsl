struct ShaderConstant
{
    ivec2 resolution;
    vec3 background_color;
};
layout(std140, binding = SGC_SHADER_CONSTANTS_BINDING_POINT) uniform ShaderConstants
{
    ShaderConstant shader_constants;
};	