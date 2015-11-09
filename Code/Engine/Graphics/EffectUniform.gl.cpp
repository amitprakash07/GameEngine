#include "Effect.h"

bool Engine::Graphics::Effect::ReadUniforms()
{
	/*
	s_uniformLocalToWorld - g_transform_localToWorld
	s_uniformWorldToView - g_transform_worldToView
	s_uniformViewToScreen -g_transform_viewToScreen
	*/
	s_uniformLocalToWorld = glGetUniformLocation(s_programId, "g_transform_localToWorld");
	s_uniformWorldToView = glGetUniformLocation(s_programId, "g_transform_worldToView");
	s_uniformViewToScreen = glGetUniformLocation(s_programId, "g_transform_viewToScreen");
	if (s_uniformLocalToWorld == -1 && s_uniformWorldToView == -1 && s_uniformViewToScreen == -1)
		return false;

	return true;
}
