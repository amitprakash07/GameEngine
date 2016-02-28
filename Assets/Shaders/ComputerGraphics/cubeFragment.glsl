/*
Fragment shader
*/

#version 410 core

uniform vec3 g_PixelColorModifier;
uniform sampler2D g_TextureSampler;

//Input
layout(location = 0) in vec4 i_color;
layout(location = 1) in vec3 i_local_normal;
layout(location = 2) in vec3 i_local_tangent;
layout(location = 3) in vec3 i_local_bi_tangent;
layout(location = 4) in vec2 i_local_texture;

//Output
out vec4 o_color;

void main()
{
	o_color.rgb = i_color.rgb * g_PixelColorModifier;
	o_color.a = i_color.a;
	o_color = o_color * texture2D(g_TextureSampler, i_local_texture);
}