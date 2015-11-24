#include "Effect.h"

bool Engine::Graphics::Effect::ReadEngineUniformsHandle()
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


//bool Engine::Graphics::Effect::setMaterialUniformHandle(char* uniformName, int i_index)
//{
//	if (i_index <= materialUniformCount)
//	{
//		size_t length = strlen(uniformName);
//#ifdef _DEBUG
//		materialUniformNames[i_index] = new char[length];
//		memcpy(materialUniformNames[i_index], uniformName, sizeof(char)*length);
//		materialUniformNames[i_index][length] = '\0';
//#endif
//		materialUniforms[i_index].Handle = glGetUniformLocation(s_programId, uniformName);
//		if (materialUniforms[i_index].Handle == -1)
//			return false;
//
//		return true;
//	}
//	return false;
//}



