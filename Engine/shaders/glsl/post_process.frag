#version 420 core

out vec3 out_color;

layout(binding = 0) uniform sampler2D render_texture;

in vec2 UV;

void main()
{	
	const float exposure = 1.0;
	const float gamma = 2.2;
    vec3 hdrColor = texture(render_texture, UV).rgb;
    vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);
    mapped = pow(mapped, vec3(1.0 / gamma));
  
    out_color = mapped;
}