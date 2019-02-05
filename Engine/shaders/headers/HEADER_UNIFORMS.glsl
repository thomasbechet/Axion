struct ShaderConstant
{
    ivec2 resolution;
};
layout(std140, binding = SGC_SHADER_CONSTANTS_UBO_BINDING_POINT) uniform ShaderConstants
{
    ShaderConstant shader_constants;
};	