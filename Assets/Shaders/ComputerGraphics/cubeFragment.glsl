/*
Fragment shader
*/

#version 410 core

uniform vec3 g_PixelColorModifier = vec3(1.0);
uniform sampler2D g_TextureSampler;

uniform lightUniforms
{
	vec3 lightPosition;
	float intensity;
	vec3 lightColor;
};

//Input
layout(location = 0) in vec4 i_color;
layout(location = 1) in vec3 i_local_normal;
layout(location = 2) in vec3 i_local_tangent;
layout(location = 3) in vec3 i_local_bi_tangent;
layout(location = 4) in vec2 i_local_texture;
layout(location = 5) in vec3 i_positionInView;

//Output
out vec4 o_color;

void main()
{
	o_color.rgb = i_color.rgb * g_PixelColorModifier;
	o_color.a = i_color.a;
	o_color = o_color * texture2D(g_TextureSampler, i_local_texture);
	float diffuse = max(0.0, dot(i_local_normal, lightPosition - i_positionInView));
	vec3 diffuse_color = (diffuse * intensity) * lightColor;
	o_color = o_color * vec4(diffuse_color,1.0);
}