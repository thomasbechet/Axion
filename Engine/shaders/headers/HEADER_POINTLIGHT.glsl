struct PointLight
{
    vec3 position;
    float radius;
    vec3 color;
    float intensity;
};
layout(std140, binding = SGC_POINTLIGHT_UBO_BINDING_POINT) uniform PointLights
{ 
    PointLight point_lights[SGC_POINTLIGHT_MAX_NUMBER];
    uint point_light_count;
};