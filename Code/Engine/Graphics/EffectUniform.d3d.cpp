#include "Effect.h"

bool Engine::Graphics::Effect::ReadUniforms()
{

	/*
	s_uniformLocalToWorld - g_transform_localToWorld 
	s_uniformWorldToView - g_transform_worldToView
	s_uniformViewToScreen -g_transform_viewToScreen
	*/

	if (s_constantsTable)
	{
		s_uniformLocalToWorld = s_constantsTable->GetConstantByName(nullptr, "g_transform_localToWorld");
		s_uniformWorldToView = s_constantsTable->GetConstantByName(nullptr, "g_transform_worldToView");
		s_uniformViewToScreen = s_constantsTable->GetConstantByName(nullptr, "g_transform_viewToScreen");

		if (s_uniformLocalToWorld != nullptr && s_uniformWorldToView != nullptr && s_uniformViewToScreen != nullptr)
			return true;
	}

	return false;
}
