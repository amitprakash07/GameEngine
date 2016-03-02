/*
Fragment shader
*/

#version 410 core

uniform vec3 g_PixelColorModifier;
uniform samplerCube g_TextureSampler;

//Input
layout(location = 0) in vec4 i_color;
// Normal in eye space
layout(location = 1) in vec3 i_normal_eye;
layout(location = 2) in vec3 i_local_tangent;
layout(location = 3) in vec3 i_local_bi_tangent;
layout(location = 4) in vec2 i_local_texture;
layout(location = 5) in mat4 i_viewMatrix;
//position in eye space
layout(location = 6) in vec3 i_position_in_eye; 


//Output
out vec4 o_color;

void main()
{
	o_color.rgb = i_color.rgb * g_PixelColorModifier;
	o_color.a = i_color.a;
	vec3 normalizedNormalInEye = normalize(i_normal_eye);
	vec3 normalizedViewVector = normalize(i_position_in_eye);
	//Calculating the reflection Vector in View Space
	vec3 reflectedVectorInEye = reflect(normalizedViewVector, normalizedNormalInEye);

	//Calculating reflection vector in World Space
	vec3 reflectedVectorInWorld = vec3(vec4(reflectedVectorInEye, 0) * inverse(i_viewMatrix));
	o_color = o_color * texture(g_TextureSampler, reflectedVectorInEye);
}