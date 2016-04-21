/*
CubeFragmentWithNormalMapping
Fragment shader
*/

#version 410 core

uniform vec3 g_PixelColorModifier = vec3(1.0);
uniform sampler2D g_TextureSampler;
uniform mat4  g_transform_worldToView;
uniform vec3 specularColor;
uniform float glossiness;
uniform sampler2D g_NormalMapSampler;
uniform float ambientLight = 0.0;

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
layout(location = 5) in vec3 i_viewVector;
layout(location = 6) in vec3 i_lightDirectionInTangentSpace;

//Output
out vec4 o_color;

void main()
{
	vec3 normalFromNormalMap = (texture(g_NormalMapSampler, i_local_texture).rgb * 2.0) - vec3(1.0);
	vec3 viewVector = normalize(-(i_viewVector));
	vec3 halfVector = normalize(i_lightDirectionInTangentSpace + viewVector);
	o_color.rgb = i_color.rgb * g_PixelColorModifier;
	o_color.a = i_color.a;

	o_color = o_color * texture(g_TextureSampler, i_local_texture);

	float diffuse = max(0.0, dot(normalFromNormalMap, i_lightDirectionInTangentSpace)) * intensity;
	if (diffuse > 0.95)
		diffuse = 0.95;
	else if (diffuse > 0.5)
		diffuse = 0.5;
	else if (diffuse > 0.25)
		diffuse = 0.25;
	else
		diffuse = 0;
	vec3 diffuseCol = diffuse *lightColor;

	float  specular = pow(max(0.0, dot(normalFromNormalMap, halfVector)), glossiness) * intensity;
	if (specular > 0.95)
		specular = 0.95;
	else if (specular > 0.5)
		specular = 0.5;
	else if (specular > 0.25)
		specular = 0.25;
	else
		specular = 0;

	
	vec3 specColor = specular * lightColor * specularColor;
	vec3 ambient = vec3(o_color * ambientLight);
	o_color.rgb = o_color.rgb * (diffuseCol + specColor + vec3(ambientLight));
	//vec4 tempCol = o_color.rgb * (diffuse + specular + vec3(ambientLight));
}