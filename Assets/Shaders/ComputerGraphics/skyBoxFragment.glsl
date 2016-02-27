/*
Fragment shader
*/

#version 410 core

uniform vec3 g_PixelColorModifier;
uniform samplerCube g_TextureSampler;

//Input
layout(location = 0) in vec3 i_local_texture;

//Output
out vec4 o_color;

void main()
{
	o_color = texture(g_TextureSampler, i_local_texture);
	o_color = o_color * vec4(g_PixelColorModifier,1);
}