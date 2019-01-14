#version 420 core

layout(location = 0) out vec3 out_color;

layout(binding = 0) uniform sampler2D gbuffer_albedo_specular;
layout(binding = 1) uniform sampler2D gbuffer_normal;
layout(binding = 2) uniform sampler2D gbuffer_depth_stencil;

in vec2 UV;

#define USE_CAMERA_UNIFORM_BLOCK 1
#if USE_CAMERA_UNIFORM_BLOCK

	#define CAMERA_BINDING_POINT 2

	layout(std140, binding = CAMERA_BINDING_POINT) uniform Camera
	{
		mat4 camera_view;
		mat4 inv_camera_projection;
	};

#endif

#define USE_POINTLIGHT_UNIFORM_BLOCK 1 
#if USE_POINTLIGHT_UNIFORM_BLOCK

	#define POINTLIGHT_MAX_NUMBER 50
	#define POINTLIGHT_BINDING_POINT 3
	#define POINTLIGHT_INDEXES_BINDING_POINT 4

	struct PointLight
	{
		vec3 position;
		float radius;
		vec3 color;
		float intensity;
	};
	layout(std140, binding = POINTLIGHT_BINDING_POINT) uniform PointLights
	{
		PointLight point_lights[POINTLIGHT_MAX_NUMBER];
	};
	layout(packed, binding = POINTLIGHT_INDEXES_BINDING_POINT) uniform PointLightsIndexes
	{
		uint point_light_index[POINTLIGHT_MAX_NUMBER];
		uint point_light_count;
	};

	PointLight getPointLight(uint i)
	{
		return point_lights[point_light_index[i]];
	}

#endif

vec3 viewPosFromDepth(float depth)
{
    float z = depth * 2.0 - 1.0;

    vec4 clipSpacePosition = vec4(UV * 2.0 - 1.0, z, 1.0);
    vec4 viewSpacePosition = inv_camera_projection * clipSpacePosition;

    //Perspective division
    viewSpacePosition /= viewSpacePosition.w;

    return viewSpacePosition.xyz;
}

vec3 computePointLight(PointLight light, vec3 albedo, vec3 normal, vec3 fragPos)
{
	vec3 lightDir = normalize(light.position - fragPos);
    float diffCoeff = max(dot(normal, lightDir), 0.0);    
    vec3 diffuse  = vec3(1.0f, 1.0f, 1.0f) * diffCoeff * albedo;
    
	vec3 incidenceVector = normalize(fragPos - light.position); //a unit vector
	vec3 reflectionVector = reflect(incidenceVector, normal); //also a unit vector
	vec3 surfaceToCamera = normalize(-fragPos); //also a unit vector
	float cosAngle = max(0.0, dot(surfaceToCamera, reflectionVector));
	float specularCoefficient = pow(cosAngle, 50.0f);

	return (diffuse + specularCoefficient * vec3(1.0f, 1.0f, 1.0f));
}

void main()
{
	vec3 color = vec3(0.0f, 0.0f, 0.0f);

	vec3 albedo = texture2D(gbuffer_albedo_specular, UV).rgb;
	vec3 normal = texture2D(gbuffer_normal, UV).rgb;
	vec3 fragPos = viewPosFromDepth(texture2D(gbuffer_depth_stencil, UV).r);

	for(uint i = 0; i < point_light_count; i++)
	{
		color += computePointLight(getPointLight(i), albedo, normal, fragPos); 
	}
	
	out_color = color;
}