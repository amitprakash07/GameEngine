/*
	Fragment shader
*/

#version 410 core

uniform vec3 g_PixelColorModifier;
uniform sampler2D g_TextureSampler;

layout( location = 0 ) in vec2 i_texturteCoordiante;

out vec4 o_color;

void main()
{
	o_color = texture2D( g_TextureSampler, i_texturteCoordiante);
	o_color.rgb = o_color.rgb * g_PixelColorModifier;	
}

