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
//#version 330
#version 410 core

// This extension is required in order to specify explicit locations for shader inputs and outputs
//#extension GL_ARB_separate_shader_objects : require


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

void diffuse(const in vec3 iNormal,
const in vec3 iLightDirection,
const in vec3 difuseAlbedo,
out vec3 o_DiffuseColor)
{
	vec3 lightVector = -iLightDirection;
    float geometryTerm = dot(iNormal, lightVector);    
    o_DiffuseColor = max(0.0,geometryTerm) * difuseAlbedo;
}


void specular(const in vec3 iViewVector,
const in vec3 iNormal,
const in vec3 iLightDirection,
const in vec3 specularAlbedo,
const in float specularGlossiness,
out vec3 o_specularColor )
{
    vec3 normal = normalize(iNormal);
    vec3 lightDirection = normalize(iLightDirection);
    vec3 viewVector = normalize(iViewVector);

    vec3 reflectionVector = reflect(-lightDirection,normal);
    float geometryTerm = dot(reflectionVector,viewVector);

    o_specularColor = pow(max(geometryTerm,0.0),specularGlossiness) * specularAlbedo;

}