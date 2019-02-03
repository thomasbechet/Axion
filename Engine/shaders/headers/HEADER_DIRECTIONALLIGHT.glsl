struct DirectionalLight
{
    vec3 direction;
    float pad;
    vec3 color;
    float intensity;
};
layout(std140, binding = SGC_DIRECTIONALLIGHT_UBO_BINDING_POINT) uniform DirectionalLights
{
    DirectionalLight directional_lights[SGC_DIRECTIONALLIGHT_MAX_NUMBER];
    uint directional_lights_count;
};
