/*
Vertex shader with vertex color
attribute modifier
*/

#version 410 core

uniform mat4  g_transform_localToWorld;
uniform mat4  g_transform_worldToView;
uniform mat4  g_transform_viewToScreen;
//uniform vec4 vertexColorModifier;


//Input
layout(location = 0) in vec3 i_local_position;

//Output
layout(location = 0) out vec3 o_local_texture;

void main()
{
	vec4 position_world = vec4(i_local_position, 1.0) * g_transform_localToWorld;
	vec3 position_view = vec3(position_world) * mat3(g_transform_worldToView);
	vec4 screenPosition = vec4(position_view,1) * g_transform_viewToScreen;
	gl_Position = screenPosition;
	o_local_texture = i_local_position;	
	//gl_Position = vec4(i_local_position,1.0);
	//vec4 skyBoxTexture = vec4(i_local_position,1.0) * g_transform_worldToView;
	//o_local_texture = skyBoxTexture.xyz;
}