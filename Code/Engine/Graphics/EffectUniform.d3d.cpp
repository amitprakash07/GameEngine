#include "Effect.h"

//bool Engine::Graphics::Effect::ReadEngineUniformsHandle()
//{
//
//	/*
//	s_uniformLocalToWorld - g_transform_localToWorld 
//	s_uniformWorldToView - g_transform_worldToView
//	s_uniformViewToScreen -g_transform_viewToScreen
//	*/
//
//	if (s_vertexShaderConstantTable)
//	{
//		s_uniformLocalToWorld = s_vertexShaderConstantTable->GetConstantByName(nullptr, "g_transform_localToWorld");
//		s_uniformWorldToView = s_vertexShaderConstantTable->GetConstantByName(nullptr, "g_transform_worldToView");
//		s_uniformViewToScreen = s_vertexShaderConstantTable->GetConstantByName(nullptr, "g_transform_viewToScreen");
//
//		if (s_uniformLocalToWorld != nullptr && s_uniformWorldToView != nullptr && s_uniformViewToScreen != nullptr)
//			return true;
//	}
//
//	return false;
//}


//bool Engine::Graphics::Effect::setMaterialUniformHandle(char* i_uniformName, int i_index)
//{
//	if (i_index <= materialUniformCount)
//	{
//		size_t length = strlen(i_uniformName);
//#ifdef _DEBUG
//		materialUniformNames[i_index] = new char[length];
//		memcpy(materialUniformNames[i_index], i_uniformName, sizeof(char)*length);
//		materialUniformNames[i_index][length] = '\0';
//#endif
//		switch (materialUniforms[i_index].type)
//		{
//		case Engine::Graphics::Vertex:
//			materialUniforms[i_index].Handle = s_vertexShaderConstantTable->GetConstantByName(nullptr, i_uniformName);
//			break;
//		case Engine::Graphics::Fragment:
//			materialUniforms[i_index].Handle = s_fragmentShaderConstantTable->GetConstantByName(nullptr, i_uniformName);
//			break;
//		case Unknown:
//			break;
//		}
//		if (materialUniforms[i_index].Handle == nullptr)
//			return false;
//
//		return true;
//	}
//	return false;
//}

