#version 430 core

// Samplers for pre-rendered color, normal, position and depth
layout(binding = 0) uniform sampler2D glNormalTexture;
layout(binding = 1) uniform sampler2D glViewPositionTexture;
layout(binding = 2) uniform sampler2D glDepthTexture;
layout(binding = 3) uniform sampler2D glColorTexture;

layout(location = 0) in vec2 texCoord;

uniform float radius = 5;
uniform uint sampleCount = 256;
uniform mat4 g_transform_viewToScreen;
uniform vec4 ambientLightColor = vec4(0.4);
uniform float ambientIntensity = 1.0;
uniform bool ambientOnly = false;

layout(binding = 0, std140) uniform SAMPLE_POINTS
{
	vec4 pos[256];
	vec4 random_vectors[256];
} points;


layout(location = 0) out vec4 color;


void main(void)
{
	vec2 P = gl_FragCoord.xy / textureSize(glNormalTexture, 0);
	vec4 NormalAndDepth = textureLod(glNormalTexture, P, 0);
	//vec3 viewSpacePosition = texture(glNormalTexture, texCoord).xyz;
	//float z = texture(glViewPositionTexture, texCoord).xyz;
	float z = NormalAndDepth.w;
	float x = texCoord.x * 2 - 1.0;
	float y = (1 - texCoord.y) * 2 - 1;
	vec4 viewSpaceProjectedPosition = vec4(x, y, z, 1.0);
	vec4 unprojectedPosition = viewSpaceProjectedPosition * inverse(g_transform_viewToScreen);
	vec3 viewSpacePosition = unprojectedPosition.xyz / unprojectedPosition.w;
	float ambientOcclusionFactor = 0.0;

	for (int i = 0; i < sampleCount; i++)
	{
		vec3 samplePositionVec3 = viewSpacePosition + (vec3(points.pos[i])* radius) ;
		vec4 samplePosition = vec4(samplePositionVec3, 1.0);
		//Sample Point in View Space as sample Points is in screen space
		samplePosition = samplePosition * g_transform_viewToScreen;
		//Perspective Division
		samplePosition.xy /= samplePosition.w;
		//Scale and Bias in range of 0-1
		//Using multiplication rather division for precision
		samplePosition.xy = (samplePosition.xy * 0.5) + vec2(0.5); 

		float sampleDepthInDepthTexture = textureLod(glNormalTexture, samplePosition.xy, 0).b;

		float rangeCheck = abs(viewSpacePosition.z - sampleDepthInDepthTexture) < radius ? 1.0 : 0.0;
		ambientOcclusionFactor += (sampleDepthInDepthTexture <= samplePosition.z ? 1.0 : 0.0) * rangeCheck;
	}

	ambientOcclusionFactor = 1.0 - (ambientOcclusionFactor / sampleCount);
	vec4 ambientTotal = ambientLightColor * ambientOcclusionFactor * ambientIntensity;

	if (!ambientOnly)
		color = textureLod(glColorTexture, P, 0) + ambientTotal;
	else
		color = ambientTotal;

}
