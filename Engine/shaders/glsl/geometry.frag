#version 430 core

layout(early_fragment_tests) in;
layout(location = 0) out vec3 out_normal;

in vec2 UV;
in vec3 NORMAL;
in mat3 TBN;

layout(binding = $DIFFUSE_TEXTURE_BINDING) uniform sampler2D diffuse_texture;
layout(binding = $NORMAL_TEXTURE_BINDING) uniform sampler2D normal_texture;
layout(binding = $SPECULAR_TEXTURE_BINDING) uniform sampler2D specular_texture;

layout(location = $MATERIAL_INDEX_LOCATION) uniform uint material_index;

struct Material
{
    uint flags;
    vec3 diffuse_color;
};
layout(std140, binding = $MATERIAL_UBO_BINDING_POINT) uniform Materials
{
    Material materials[$MATERIAL_MAX_NUMBER];	
};

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

void main()
{
	out_normal = getNormal();
}