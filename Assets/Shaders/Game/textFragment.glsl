#version 430 core
in vec2 TexCoords;
uniform sampler2D text;
uniform vec4 textColor = vec4(1.0);

void main()
{
	gl_FragColor = vec4(1, 1, 1, texture2D(text, TexCoords).r) * textColor;
}