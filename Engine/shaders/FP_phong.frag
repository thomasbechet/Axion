#version 420 core

layout(location = 0) out vec3 out_color;

in vec2 UV;
in vec3 POSITION;
in vec3 NORMAL;
in vec3 COLOR;
in mat3 TBN;

layout(binding = 3) uniform sampler2D gbuffer_normal_texture;
layout(binding = 4) uniform sampler2D gbuffer_depth_stencil_texture;

#define USE_MATERIAL 1 
#if USE_MATERIAL

	#define MATERIAL_UBO_BINDING_POINT 1
	#define MATERIAL_MAX_NUMBER 50
	#define MATERIAL_USE_DIFFUSE_TEXTURE 1u
	#define MATERIAL_USE_DIFFUSE_COLOR 2u
	#define MATERIAL_USE_NORMAL_TEXTURE 4u
	#define MATERIAL_IS_BUMP_TEXTURE 8u
	#define MATERIAL_USE_SPECULAR_TEXTURE 16u

	struct Material
	{
		uint flags;
		vec3 diffuse_color;
	};
	layout(std140, binding = MATERIAL_UBO_BINDING_POINT) uniform Materials
	{
		Material materials[MATERIAL_MAX_NUMBER];	
	};

	layout(binding = 0) uniform sampler2D diffuse_texture;
	layout(binding = 1) uniform sampler2D normal_texture;
	layout(binding = 2) uniform sampler2D specular_texture;

	uniform uint material_index;

	vec3 getAlbedo()
	{
		if(bool(materials[material_index].flags & MATERIAL_USE_DIFFUSE_TEXTURE))
			return texture(diffuse_texture, vec2(UV.x, 1.0 - UV.y)).rgb;
		else if(bool(materials[material_index].flags & MATERIAL_USE_DIFFUSE_COLOR))
			return materials[material_index].diffuse_color.rgb;
		else
			return COLOR;
	}

	vec3 getNormal()
	{
		if(bool(materials[material_index].flags & MATERIAL_USE_NORMAL_TEXTURE))
		{
			if(bool(materials[material_index].flags & MATERIAL_IS_BUMP_TEXTURE))
			{
				vec2 pixel_size = 1.0 / vec2(textureSize(normal_texture, 0));

				float height_pu = texture(normal_texture, vec2(UV.x + pixel_size.x, 1.0 - UV.y), 0).r;
				float height_mu = texture(normal_texture, vec2(UV.x - pixel_size.x, 1.0 - UV.y), 0).r;
				float height_pv = texture(normal_texture, vec2(UV.x, 1.0 - UV.y + pixel_size.y), 0).r;
				float height_mv = texture(normal_texture, vec2(UV.x, 1.0 - UV.y - pixel_size.y), 0).r;
				float du = height_pu - height_mu;
				float dv = height_pv - height_mv;
				
				return TBN * normalize(vec3(-du, -dv, 1.0 / 5.0));
			}	
			else
			{
				return TBN * vec3((texture(normal_texture, vec2(UV.x, 1.0 - UV.y)).rgb * 2.0) - 1.0);
			}
		}
		else
		{
			return NORMAL;
		}
	}

#endif

#define USE_CAMERA 1
#if USE_CAMERA

	#define CAMERA_UBO_BINDING_POINT 2

	layout(std140, binding = CAMERA_UBO_BINDING_POINT) uniform Camera
	{
		mat4 camera_view;
		mat4 inv_camera_projection;
	};

#endif

#define USE_POINTLIGHT 1 
#if USE_POINTLIGHT

	#define POINTLIGHT_UBO_BINDING_POINT 3
	#define POINTLIGHT_MAX_NUMBER 50

	struct PointLight
	{
		vec3 position;
		float radius;
		vec3 color;
		float intensity;
	};
	layout(std140, binding = POINTLIGHT_UBO_BINDING_POINT) uniform PointLights
	{ 
		PointLight point_lights[POINTLIGHT_MAX_NUMBER];
		uint point_light_count;
	};

#endif

vec3 phongPointLight(PointLight light, vec3 albedo, vec3 normal, vec3 fragPos)
{
	vec3 position = light.position;

	vec3 lightDir = normalize(position - fragPos);
    float diffCoeff = max(dot(normal, lightDir), 0.0);    
    vec3 diffuse  = vec3(1.0f, 1.0f, 1.0f) * diffCoeff * albedo;
    
	vec3 incidenceVector = normalize(fragPos - position); //a unit vector
	vec3 reflectionVector = reflect(incidenceVector, normal); //also a unit vector
	vec3 surfaceToCamera = normalize(-fragPos); //also a unit vector
	float cosAngle = max(0.0, dot(surfaceToCamera, reflectionVector));
	float specularCoefficient = pow(cosAngle, 50.0f);

	return (diffuse + specularCoefficient * vec3(1.0f, 1.0f, 1.0f));
}

void main()
{
	//Determine tile index
	//ivec2 location = ivec2(gl_FragCoord.xy);
	//ivec2 tileID = location / ivec2(16, 16);
	//uint index = tileID.y * numberOfTilesX + tileID.x;

	vec3 color = vec3(0.0f, 0.0f, 0.0f);

	vec3 albedo = getAlbedo();
	vec3 normal = getNormal();

	for(uint i = 0; i < point_light_count; i++)
	{
		color += phongPointLight(point_lights[i], albedo, normal, POSITION); 
	}

	out_color = color;
}