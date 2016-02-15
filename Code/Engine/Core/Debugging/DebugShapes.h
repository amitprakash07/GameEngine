#pragma once

#ifndef __DEBUG_SHAPES_H
#define __DEBUG_SHAPES_H

#define GAME_ENGINE_DEBUG_MODE

#ifdef GAME_ENGINE_DEBUG_MODE

#include "../Utilities/SharedPointer.h"
#include "../EngineCore/Objects/MeshObject.h"
#include "../Maths/cMatrix_transformation.h"
#include "../../Graphics/typedefs.h"


namespace Engine
{
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
		static void DrawShape(ShapeTarget,
			Engine::Maths::Point3,
			float iRadius = 1.0f,
			Engine::Graphics::RGBColor = Engine::Graphics::RGBColor(0.0f, 1.0f, 0.0f)); //Sphere
		static void DrawShape(ShapeTarget,
			Engine::Maths::Point3,
			float iLength = 1.0f,
			float iWidth = 1.0f, float
			iHeight = 1.0f,
			Engine::Graphics::RGBColor = Engine::Graphics::RGBColor(0.0f, 1.0f, 0.0f)); //Box
		static void DrawShape(ShapeTarget,
			Engine::Maths::Point3,
			float iRadius = 1.0f,
			float iHeight = 1.0f,
			Engine::Graphics::RGBColor = Engine::Graphics::RGBColor(0.0f, 1.0f, 0.0f)); //Cylinder
		static void DrawShape(ShapeTarget,
			Engine::Maths::Point3,
			Engine::Maths::Point3,
			Engine::Graphics::RGBColor = Engine::Graphics::RGBColor(0.0f, 1.0f, 0.0f)); //Line
	private:
		Debug();
		static std::vector<Engine::SharedPointer<Engine::Object>> debugShapeList;
		Engine::SharedPointer<Engine::Object> debugShape;
		ShapeTarget shapeType;
	};
}
#endif

#endif