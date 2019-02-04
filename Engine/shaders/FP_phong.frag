//////////////////////////
//THIS BLOCK IS REQUIRED//
//////////////////////////
#version 430 core

layout(early_fragment_tests) in;
layout(location = 0) out vec3 out_color;

in vec2 UV;
in vec3 POSITION;
in vec3 NORMAL;
in vec3 COLOR;
in mat3 TBN;

layout(binding = 3) uniform sampler2D gbuffer_normal_texture;
layout(binding = 4) uniform sampler2D gbuffer_depth_texture;

///////////////////////////
///////////////////////////

#include GLOBAL_CONSTANTS
#include HEADER_CAMERA
#include HEADER_LIGHTS
#include HEADER_MATERIALS
#include HEADER_UNIFORMS

vec3 phongPointLight(PointLight light, vec3 albedo, vec3 normal, vec3 fragPos)
{
	vec3 position = light.position;
	float radius = light.radius;

	vec3 lightDir = normalize(position - fragPos);
    float diffCoeff = max(dot(normal, lightDir), 0.0);
	float ambientCoeff = 0.05f;
    vec3 diffuse  = vec3(1.0f, 1.0f, 1.0f) * diffCoeff * albedo;
    
	vec3 incidenceVector = normalize(fragPos - position); //a unit vector
	vec3 reflectionVector = reflect(incidenceVector, normal); //also a unit vector
	vec3 surfaceToCamera = normalize(-fragPos); //also a unit vector
	float cosAngle = max(0.0, dot(surfaceToCamera, reflectionVector));
	float specularCoefficient = pow(cosAngle, 50.0f);
	//specularCoefficient = 0.0f;

	float attenuation = smoothstep(radius, 0, length(fragPos - position));

	if(length(fragPos - position) > radius) return vec3(0, 0, 0);

	return ((diffuse + specularCoefficient * vec3(1.0f, 1.0f, 1.0f)) + ambientCoeff * albedo) * attenuation;
}

vec3 phongDirectionalLight(DirectionalLight light, vec3 albedo, vec3 normal, vec3 fragPos)
{
	vec3 lightDir = normalize(light.direction);
    float diffCoeff = max(dot(normal, lightDir), 0.0);
	float ambientCoeff = 0.2f;
    vec3 diffuse  = vec3(1.0f, 1.0f, 1.0f) * diffCoeff * albedo;
    
	vec3 incidenceVector = -lightDir; //a unit vector
	vec3 reflectionVector = reflect(incidenceVector, normal); //also a unit vector
	vec3 surfaceToCamera = normalize(-fragPos); //also a unit vector
	float cosAngle = max(0.0, dot(surfaceToCamera, reflectionVector));
	float specularCoefficient = pow(cosAngle, 50.0f);

	return ((diffuse + specularCoefficient * vec3(1.0f, 1.0f, 1.0f)) + ambientCoeff * albedo);
}

void main()
{
	vec3 color = vec3(0.0f, 0.0f, 0.0f);

	vec3 albedo = getAlbedo();
	vec3 normal = getNormal();

	/*//No culling prepass
	for(uint i = 0; i < point_light_count; i++)
	{
		PointLight light = point_lights[i];
		color += phongPointLight(light, albedo, normal, POSITION); 
	}*/

	//Culling prepass
	uint tileID = getCullID();
	uint key = tileID * SGC_POINTLIGHT_CULL_MAX_NUMBER;
	uint i;
	for(i = 0; isPointLightCullIndexValid(key, i); i++)
	{
		PointLight pointLight = point_lights[getPointLightCullIndex(key, i)];
		color += phongPointLight(pointLight, albedo, normal, POSITION); 
	}

	float I = float(i) / 5.0f;

	//Adding directional light
	for(i = 0; i < directional_lights_count; i++)
	{
		DirectionalLight light = directional_lights[i];
		color += phongDirectionalLight(light, albedo, normal, POSITION);
	}

	float v = (float(getCullID()) / float(SGC_CULL_TILE_SIZE * SGC_CULL_TILE_SIZE));
	
	color = vec3(I, I, I);

	out_color = color;
}