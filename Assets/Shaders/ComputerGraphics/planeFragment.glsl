/*
Fragment shader
*/

#version 410 core

uniform vec3 g_PixelColorModifier;
uniform sampler2D g_TextureSampler;

//Input
layout(location = 0) in vec2 i_local_texture;
layout(location = 1) in vec3 i_local_normal;


//Output
out vec4 o_color;

void main()
{
	o_color = texture(g_TextureSampler, i_local_texture);
	o_color.rgb = o_color.rgb * g_PixelColorModifier;
	o_color.a = 1.0;
}