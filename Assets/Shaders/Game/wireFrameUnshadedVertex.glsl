/*
Vertex shader with vertex color
attribute modifier
*/
#version 410 core
uniform mat4 g_ScaleTransform = mat4(1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0);
uniform mat4  g_transform_localToWorld = mat4(1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0);
uniform mat4  g_transform_worldToView  = mat4(1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0);
uniform mat4  g_transform_viewToScreen = mat4(1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0);
uniform vec4 vertexColorModifier = vec4(1.0);


layout(location = 0) in vec3 i_local_position;
layout(location = 1) in vec3 i_local_normal;
layout(location = 2) in vec3 i_local_tangent;
layout(location = 3) in vec3 i_local_bi_tangent;
layout(location = 4) in vec2 i_local_texture;
layout(location = 5) in vec4 i_color;

layout(location = 0) out vec2 o_texturteCoordiante;
layout(location = 1) out vec4 o_color;


void main()
{
	vec4 scaledPosition = vec4(i_local_position, 1.0) * g_ScaleTransform;
	vec4 position_world = scaledPosition * g_transform_localToWorld;
	vec4 position_view = position_world * g_transform_worldToView;
	vec4 clipSpacePosition = position_view * g_transform_viewToScreen;
	gl_Position = clipSpacePosition;
	o_color = i_color*vertexColorModifier ;	
	o_texturteCoordiante = i_local_texture;
}
