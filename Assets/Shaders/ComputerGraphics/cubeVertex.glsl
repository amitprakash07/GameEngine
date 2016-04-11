/*
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
layout(location = 5) out vec3 o_positionInView;

void main()
{

	vec4 scaledPosition = vec4(i_local_position, 1.0) * g_ScaleTransform;
	vec3 normal = i_local_normal * mat3(g_normalMatrix);
	normal = normalize(normal);
	vec4 position_world = scaledPosition * g_transform_localToWorld;
	vec4 position_view = position_world * g_transform_worldToView;
	vec4 screenPosition = position_view * g_transform_viewToScreen;

	o_positionInView = vec3(position_view);
	gl_Position = screenPosition;
	o_color = i_color*vertexColorModifier;
	o_local_normal = normal;
	o_local_tangent = i_local_tangent;
	o_local_bi_tangent = i_local_bi_tangent;	
	o_local_texture = i_local_texture;
}