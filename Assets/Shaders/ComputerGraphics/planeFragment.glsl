/*
PlaneFreagmentSahder
Fragment shader
*/

#version 410 core

uniform vec3 g_PixelColorModifier;
uniform sampler2D g_TextureSampler;
uniform mat4  g_transform_worldToView;

uniform vec3 specularColor;
uniform float glossiness;

uniform lightUniforms
{
	vec3 lightPosition;
float intensity;
vec3 lightColor;
};
//Input
layout(location = 0) in vec2 i_local_texture;
layout(location = 1) in vec3 i_local_normal;
layout(location = 2) in vec3 i_positionInView;


//Output
out vec4 o_color;

void main()
{
	vec3 lightPositionInView = vec3(vec4(lightPosition, 1.0) * g_transform_worldToView);
	vec3 lightDirection = normalize(lightPositionInView - i_positionInView);
	vec3 viewVector = normalize(-(i_positionInView));
	vec3 halfVector = normalize(lightDirection + viewVector);

	o_color = texture2D(g_TextureSampler, i_local_texture);
	o_color = o_color * vec4(g_PixelColorModifier, 1.0);


	vec3 diffuse = max(0.0, dot(i_local_normal, lightDirection)) * intensity * lightColor;
	vec3 specular = pow(max(0.0, dot(i_local_normal, halfVector)), glossiness) * intensity * specularColor * lightColor;
	vec3 diffuse_color = (diffuse * intensity) * lightColor;
	o_color.rgb = o_color.rgb *(diffuse + specular);
}