struct Material
{
    uint flags;
    vec3 diffuse_color;
};
layout(std140, binding = SGC_MATERIAL_UBO_BINDING_POINT) uniform Materials
{
    Material materials[SGC_MATERIAL_MAX_NUMBER];	
};

layout(binding = 0) uniform sampler2D diffuse_texture;
layout(binding = 1) uniform sampler2D normal_texture;
layout(binding = 2) uniform sampler2D specular_texture;

uniform uint material_index;

vec3 getAlbedo()
{
    if(bool(materials[material_index].flags & SGC_MATERIAL_USE_DIFFUSE_TEXTURE))
        return texture(diffuse_texture, vec2(UV.x, 1.0 - UV.y)).rgb;
    else if(bool(materials[material_index].flags & SGC_MATERIAL_USE_DIFFUSE_COLOR))
        return materials[material_index].diffuse_color.rgb;
    else
        return COLOR;
}

vec3 getNormal()
{
    if(bool(materials[material_index].flags & SGC_MATERIAL_USE_NORMAL_TEXTURE))
    {
        if(bool(materials[material_index].flags & SGC_MATERIAL_IS_BUMP_TEXTURE))
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