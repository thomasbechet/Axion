#version 430 core

layout(location = 0) out vec3 out_normal;

in vec2 UV;
in vec3 NORMAL;
in mat3 TBN;

#define USE_MATERIAL_UNIFORM_BLOCK 1 
#if USE_MATERIAL_UNIFORM_BLOCK

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

	layout(binding = 0) uniform sampler2D normal_texture;

	uniform uint material_index;

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

void main()
{
	out_normal = getNormal();
}