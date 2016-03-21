/*
	Vertex shader
*/

#version 410 core

layout( location = 0) in vec3 i_position;
layout(location = 1) in vec2 i_textureCoordinate;
layout(location = 0) out vec2 o_textureCoordinate;

void main()
{
	gl_Position = vec4(i_position, 1.0);
	o_textureCoordinate = i_textureCoordinate;
	o_textureCoordinate.y = 1 - o_textureCoordinate.y;
}

