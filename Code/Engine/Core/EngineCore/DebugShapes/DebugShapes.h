#pragma once

#ifndef __DEBUG_SHAPES_H
#define __DEBUG_SHAPES_H

#define GAME_ENGINE_DEBUG_MODE

#ifdef GAME_ENGINE_DEBUG_MODE

#include "../Utilities/SharedPointer.h"
#include "../../EngineCore/Objects/MeshObject.h"
#include "../Maths/cMatrix_transformation.h"


namespace Engine
{
	Math::cVector Green = { 0.0f,1.0f,0.0f };
	enum ShapeTarget
	{
		SPHERE = 0, //Needs radius,position
		BOX = 1, //Need Position, length, breadth,height
		CYLINDER = 2, //Need position, radius, height
		LINE = 3 //Need two positions
	};

	class Debug
	{
	public:
		static bool IsDebugShapesAvailable();
		static void drawShape(ShapeTarget,
			Math::cVector,
			float iRadius = 1.0f,
			Math::cVector = Green); //Sphere
		static void drawShape(ShapeTarget,
			Math::cVector,
			float iLength = 1.0f,
			float iWidth = 1.0f, float
			iHeight = 1.0f,
			Math::cVector = Green); //Box
		static void drawShape(ShapeTarget,
			Math::cVector,
			float iRadius = 1.0f,
			float iHeight = 1.0f,
			Math::cVector = Green); //Cylinder
		static void drawShape(ShapeTarget,
			Math::cVector,
			Math::cVector,
			Math::cVector = Green); //Line
	private:
		static std::vector<Engine::SharedPointer<Engine::GameObject>> debugShapeList;
		Engine::SharedPointer<Engine::GameObject> debugShape;
		ShapeTarget shapeType;
	};
}
#endif

#endif

//#include "DebugShapes.h"
//#include "../EngineCore/Objects/GameObject.h"
//
//std::vector<Engine::SharedPointer<Engine::GameObject>> Engine::Debug::debugShapeList;
//
//bool Engine::Debug::IsDebugShapesAvailable()
//{
//	return debugShapeList.size();
//}
//
//
////Line
//void Engine::Debug::drawShape(ShapeTarget i_shapeType,
//	Math::cVector iStartPoint,
//	Math::cVector iEndPoint,
//	Math::cVector iColor)
//{
//
//}
//
////Sphere
//void Engine::Debug::drawShape(ShapeTarget iShapeType,
//	Math::cVector iCenter,
//	float iRadius,
//	Math::cVector iColor)
//{
//
//}
//
////Box
//void Engine::Debug::drawShape(ShapeTarget iShapeType,
//	Math::cVector,
//	float iLength,
//	float iWidth,
//	float iHeight,
//	Math::cVector iColor)
//{
//
//}
//
////Cylinder
//void Engine::Debug::drawShape(ShapeTarget,
//	Math::cVector,
//	float iRadius,
//	float iHeight,
//	Math::cVector iColor)
//{
//
//}
//
//
//
//
