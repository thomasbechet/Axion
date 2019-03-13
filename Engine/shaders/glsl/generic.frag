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

layout(binding = $GBUFFER_NORMAL_TEXTURE_BINDING) uniform sampler2D gbuffer_normal_texture;
layout(binding = $GBUFFER_DEPTH_TEXTURE_BINDING) uniform sampler2D gbuffer_depth_texture;

///////////////////////////

//CONSTANTS//
struct Constant
{
    ivec2 resolution;
};
layout(std140, binding = $CONSTANTS_UBO_BINDING_POINT) uniform Constants
{
    Constant constants;
};

//POINT LIGHTS//
struct PointLight 
{
    vec3 position;
    float radius;
    vec3 color;
    float intensity;
};
layout(std140, binding = $POINT_LIGHT_UBO_BINDING_POINT) uniform PointLights
{ 
    PointLight point_lights[$POINT_LIGHT_MAX_NUMBER];
    uint point_light_count;
};

#if ($USE_LIGHT_CULLING == 1)
    layout(packed, binding = $CULL_POINT_LIGHT_SSBO_BINDING_POINT) readonly buffer PointLightsCullIndices
    {
        uint point_lights_cull_indices[];
    };

    uint getCullKey()
    {
        ivec2 tileID = ivec2(gl_FragCoord.xy) / $CULL_TILE_SIZE;
        return (tileID.y * (constants.resolution.x / $CULL_TILE_SIZE) + tileID.x) * $CULL_POINT_LIGHT_MAX_PER_TILE;
    }
    PointLight getCullPointLight(uint index, uint cullKey)
    {
        return point_lights[point_lights_cull_indices[cullKey + index + 1]];
    }
    uint getCullPointLightCount(uint cullKey)
    {
        return point_lights_cull_indices[cullKey];
    }
#else
    uint getPointLightCount()
    {
        return point_light_count;
    }
    PointLight getPointLight(uint index)
    {
        return point_lights[index];
    }
#endif

//DIRECTIONAL LIGHTS//
struct DirectionalLight
{
    vec3 direction;
    float pad;
    vec3 color;
    float intensity;
};
layout(std140, binding = $DIRECTIONAL_LIGHT_UBO_BINDING_POINT) uniform DirectionalLights
{
    DirectionalLight directional_lights[$DIRECTIONAL_LIGHT_MAX_NUMBER];
    uint directional_lights_count;
};

uint getDirectionalLightCount()
{
    return directional_lights_count;
}
DirectionalLight getDirectionalLight(uint index)
{
    return directional_lights[index];
}

//MATERIAL//
struct Material
{
    uint flags;
    vec3 diffuse_color;
    float specular_uniform;
};
layout(std140, binding = $MATERIAL_UBO_BINDING_POINT) uniform Materials
{
    Material materials[$MATERIAL_MAX_NUMBER];
};

layout(binding = $DIFFUSE_TEXTURE_BINDING) uniform sampler2D diffuse_texture;
layout(binding = $NORMAL_TEXTURE_BINDING) uniform sampler2D normal_texture;
layout(binding = $SPECULAR_TEXTURE_BINDING) uniform sampler2D specular_texture;

layout(location = $MATERIAL_INDEX_LOCATION) uniform uint material_index;

vec3 getAlbedo()
{
    if(bool(materials[material_index].flags & $MATERIAL_USE_DIFFUSE_TEXTURE))
        return texture(diffuse_texture, vec2(UV.x, 1.0 - UV.y)).rgb;
    else if(bool(materials[material_index].flags & $MATERIAL_USE_DIFFUSE_COLOR))
        return materials[material_index].diffuse_color.rgb;
    else
        return COLOR;
}
vec3 getNormal()
{
    if(bool(materials[material_index].flags & $MATERIAL_USE_NORMAL_TEXTURE))
    {
        if(bool(materials[material_index].flags & $MATERIAL_IS_BUMP_TEXTURE))
        {
            vec2 pixel_size = 1.0 / vec2(textureSize(normal_texture, 0));
            float height_pu = texture(normal_texture, vec2(UV.x + pixel_size.x, 1.0 - UV.y), 0).r;
            float height_mu = texture(normal_texture, vec2(UV.x - pixel_size.x, 1.0 - UV.y), 0).r;
            float height_pv = texture(normal_texture, vec2(UV.x, 1.0 - UV.y + pixel_size.y), 0).r;
            float height_mv = texture(normal_texture, vec2(UV.x, 1.0 - UV.y - pixel_size.y), 0).r;
            float du = height_pu - height_mu;
            float dv = height_pv - height_mv;
            return normalize(vec3(-du, -dv, 1.0 / 5.0));
        }
        else
        {
            return texture(normal_texture, vec2(UV.x, 1.0 - UV.y)).rgb * 2.0 - 1.0;
        }
    }
    else
    {
        return TBN * NORMAL;
    }
}
float getSpecular()
{
    if(bool(materials[material_index].flags & $MATERIAL_USE_SPECULAR_TEXTURE))
        return texture(specular_texture, vec2(UV.x, 1.0 - UV.y)).r;
    else
        return materials[material_index].specular_uniform;
}

///////////////////////////

vec3 blinnPointLight(PointLight light, vec3 fragPos, vec3 normal, vec3 albedo, float specular)
{
	vec3 lightDir = normalize(light.position - fragPos);
	vec3 viewDir = normalize(-fragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	
	vec3 lightColor = light.color;
	
	vec3 diff = max(dot(normal, lightDir), 0.0) * lightColor;
    vec3 spec = pow(max(dot(normal, halfwayDir), 0.0), 16.0) * lightColor;
	
	float distance = length(light.position - fragPos);
	float attenuation = smoothstep(light.radius, 0, distance);
	if(distance > light.radius) attenuation = 0.0;
	
	return (spec + diff) * albedo * attenuation;
}
vec3 blinnDirectionalLight(DirectionalLight light, vec3 fragPos, vec3 normal, vec3 albedo, float specular)
{
	vec3 lightDir = normalize(light.direction);
	vec3 viewDir = -normalize(fragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	
	vec3 lightColor = light.color;
	
	vec3 diff = max(dot(normal, lightDir), 0.0) * lightColor;
    vec3 spec = pow(max(dot(normal, halfwayDir), 0.0), 60.0) * lightColor;
	
	return (spec + diff) * albedo;
}

vec3 phongPointLight(PointLight light, vec3 fragPos, vec3 normal, vec3 albedo, float specular)
{
	vec3 lightDir = TBN * normalize(light.position - fragPos);
	vec3 viewDir = TBN * -normalize(fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	
	vec3 lightColor = light.color;
	float specularStrengh = 0.5f;
	
	vec3 diff = max(dot(normal, lightDir), 0.0) * lightColor;
    vec3 spec = min(pow(max(dot(viewDir, reflectDir), 0.0), 50), 1.0) * lightColor * specularStrengh;
	
	float distance = length(light.position - fragPos);
	float attenuation = clamp(1.0 - distance / light.radius, 0.0, 1.0);
	attenuation *= attenuation;
	if(distance > light.radius) attenuation = 0.0;
	
	diff *= attenuation;
	spec *= attenuation;
	
	return (diff + spec) * albedo;
}

vec3 phongDirectionalLight(DirectionalLight light, vec3 fragPos, vec3 normal, vec3 albedo, float specular)
{
	vec3 lightDir = TBN * normalize(light.direction);
	vec3 viewDir = TBN * -normalize(fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	
	vec3 lightColor = light.color;
	
	vec3 diff = max(dot(normal, lightDir), 0.0) * lightColor;
    vec3 spec = pow(max(dot(viewDir, reflectDir), 0.0), 10) * lightColor;
	
	return (spec + diff) * albedo;
}

void main()
{
	vec3 color = vec3(0.0f, 0.0f, 0.0f);

	vec3 albedo = getAlbedo();
	vec3 normal = getNormal();
	float specular = getSpecular();

	#if ($USE_LIGHT_CULLING == 1)
		uint cullKey = getCullKey();
		uint pointLightCount = getCullPointLightCount(cullKey);
		for(uint i = 0; i < pointLightCount; i++)
		{
			PointLight pointLight = getCullPointLight(i, cullKey);
			color += phongPointLight(pointLight, POSITION, normal, albedo, specular);
			//color += blinnPointLight(pointLight, POSITION, normal, albedo, specular);
		}
	#else
		uint pointLightCount = getPointLightCount();
		for(uint i = 0; i < pointLightCount; i++)
		{
			PointLight pointLight = getPointLight(i);
			color += phongPointLight(pointLight, POSITION, normal, albedo, specular);
			//color += blinnPointLight(pointLight, POSITION, normal, albedo, specular);
		}
	#endif

	//Adding directional light
	uint directionalLightCount = getDirectionalLightCount();
	for(uint k = 0; k < directionalLightCount; k++)
	{
		DirectionalLight light = getDirectionalLight(k);
		color += phongDirectionalLight(light, POSITION, normal, albedo, specular);
		//color += blinnDirectionalLight(light, POSITION, normal, albedo, specular);
	}

	out_color = vec3(specular / 10.0f);
	out_color = normal;
	out_color = color;
}