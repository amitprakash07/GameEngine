/*
	This file should be #included in every shader
	to set up platform-specific preprocessor directives
	so that the shader itself can be mostly platform-independent
*/

#if defined(PLATFORM_D3D)

// Translate GLSL variable types to HLSL
#define vec2 float2
#define vec3 float3
#define vec4 float4
#define mat2 float2x2
#define mat3 float3x3
#define mat4 float4x4
//For transformation
#define Transform(vector, matrix) mul(vector, matrix) 
#define O_SCREEN_POSITION o_position
#define SampleTexture(sampler, texcoords) tex2D(sampler,texcoords)

#elif defined(PLATFORM_OPEN_GL)

// The version of GLSL to use must come first
#version 330

// This extension is required in order to specify explicit locations for shader inputs and outputs
#extension GL_ARB_separate_shader_objects : require


// Translate HLSL variable types to GLSL
#define float2 vec2
#define float3 vec3
#define float4 vec4
#define float2x2 mat2
#define float3x3 mat3
#define float4x4 mat4
//For transformation
#define Transform(vector, matrix) vector * matrix
#define O_SCREEN_POSITION gl_Position
#define SampleTexture(sampler, texcoords) texture2D(sampler,texcoords)

#endif