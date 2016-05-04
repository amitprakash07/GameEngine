#version 430 core

layout(location = 0) out vec2 texCoord;

void main(void)
{
	const vec4 vertices[] = vec4[](vec4(-1.0, -1.0, 1, 1.0),
		vec4(1.0, -1.0, 1, 1.0),
		vec4(-1.0, 1.0, 1, 1.0),
		vec4(1.0, 1.0, 1, 1.0));

	gl_Position = vertices[gl_VertexID];
	texCoord = vertices[gl_VertexID].xy * 0.5 + vec2(0.5);	
}
