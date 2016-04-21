/*
CubeVertexWithNormalMapping
Vertex shader with vertex color
attribute modifier
*/

#version 410 core
uniform mat4 g_ScaleTransform = mat4(1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0);
uniform mat4  g_normalMatrix = mat4(1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0);
uniform mat4  g_transform_localToWorld;
uniform mat4  g_transform_worldToView;
uniform mat4  g_transform_viewToScreen;
uniform vec4 vertexColorModifier = vec4(1.0);

uniform lightUniforms
{
	vec3 lightPosition;
	float intensity;
	vec3 lightColor;
};

//Input
layout(location = 0) in vec3 i_local_position;
layout(location = 1) in vec3 i_local_normal;
layout(location = 2) in vec3 i_local_tangent;
layout(location = 3) in vec3 i_local_bi_tangent;
layout(location = 4) in vec2 i_local_texture;
layout(location = 5) in vec4 i_color;

//Output
layout(location = 0) out vec4 o_color;
layout(location = 1) out vec3 o_local_normal;
layout(location = 2) out vec3 o_local_tangent;
layout(location = 3) out vec3 o_local_bi_tangent;
layout(location = 4) out vec2 o_local_texture;
layout(location = 5) out vec3 o_viewVector;
layout(location = 6) out vec3 o_lightDirectionInTangentSpace;


void main()
{
	//TBN
	vec4 scaledPosition = vec4(i_local_position, 1.0) * g_ScaleTransform;
	vec3 normal = vec3(normalize(vec4(i_local_normal, 0.0) * g_normalMatrix));
	vec3 tangent = vec3(normalize(vec4(i_local_tangent, 0.0) * g_normalMatrix));
	vec3 biTangent = vec3(normalize(vec4(i_local_bi_tangent, 0.0) * g_normalMatrix));
	vec3 positionInTangentSpace;
	positionInTangentSpace.x = dot(vec3(scaledPosition), tangent);
	positionInTangentSpace.y = dot(vec3(scaledPosition), biTangent);
	positionInTangentSpace.z = dot(vec3(scaledPosition), normal);

	vec4 eyePositionInWorld = vec4(0.0, 0.0, 0.0, 1.0) * inverse(g_transform_worldToView);
	vec4 eyePositionInObjectSpace = eyePositionInWorld * inverse(g_transform_localToWorld);

	vec3 eyePositionInObjectTangentSpace;
	eyePositionInObjectTangentSpace.x = dot(vec3(eyePositionInObjectSpace), tangent);
	eyePositionInObjectTangentSpace.y = dot(vec3(eyePositionInObjectSpace), biTangent);
	eyePositionInObjectTangentSpace.z = dot(vec3(eyePositionInObjectSpace), normal);
	//Vertex Position in Tangent Space
	vec3 viewVector = positionInTangentSpace - eyePositionInObjectTangentSpace;

	o_viewVector = viewVector;

	vec4 position_world = scaledPosition * g_transform_localToWorld;
	vec4 position_view = position_world * g_transform_worldToView;
	vec4 clipSpacePosition = position_view * g_transform_viewToScreen;

	vec3 lightPositionInObjectSpace = vec3(vec4(lightPosition, 1.0) * inverse(g_transform_localToWorld));
	vec3 lightDirectionInTangentSpace;
	vec3 lightPositionInTangentSpace;
	lightPositionInTangentSpace.x = dot(lightPositionInObjectSpace, tangent);
	lightPositionInTangentSpace.y = dot(lightPositionInObjectSpace, biTangent);
	lightPositionInTangentSpace.z = dot(lightPositionInObjectSpace, normal);

	lightDirectionInTangentSpace = positionInTangentSpace - lightPositionInTangentSpace;
	lightDirectionInTangentSpace = -lightDirectionInTangentSpace;

	o_lightDirectionInTangentSpace = normalize(lightDirectionInTangentSpace);
	gl_Position = clipSpacePosition;
	o_color = i_color*vertexColorModifier;

	//Normal In Eye/ViewSpace
	o_local_texture = i_local_texture;
}