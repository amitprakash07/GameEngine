#include "DebugShapes.h"
#include "../../Windows/WindowsFunctions.h"
#include "../../Graphics/Line.h"
#include "../EngineCore/Objects/Scene.h"


std::vector<Engine::SharedPointer<Engine::Object>> Engine::Debug::debugShapeList;

bool Engine::Debug::IsDebugShapesAvailable()
{
	return debugShapeList.size();
}


//Line
void Engine::Debug::DrawShape(ShapeTarget i_shapeType,
	Engine::Maths::Point3 iStartPoint,
	Engine::Maths::Point3 iEndPoint,
	Engine::Graphics::RGBColor iColor)
{
	WindowsUtil::Assert(i_shapeType == LINE, "Shape Type is Not Line");
	Engine::Graphics::RGBAColor color;
	color.r = iColor.r;
	color.g = iColor.g;
	color.b = iColor.b;
	color.a = 1.0f;
	Engine::Graphics::Line::AddLine(
		iStartPoint, iEndPoint, color);
}

//Sphere
void Engine::Debug::DrawShape(ShapeTarget iShapeType,
	Engine::Maths::Point3 iCenter,
	float iRadius,
	Engine::Graphics::RGBColor iColor)
{
	WindowsUtil::Assert(iShapeType == SPHERE, "Shape Type is Not Sphere");
	Engine::Graphics::RGBAColor color;
	color.r = iColor.r;
	color.g = iColor.g;
	color.b = iColor.b;
	color.a = 1.0f;

	//Engine::SharedPointer<Engine::MeshObject> debugSphere =
	//Engine::MeshObject::CreateMeshObject("Arena/wallsMaterialMesh.mesh", "Arena/wallsMaterial.mat");
	Engine::SharedPointer<Engine::MeshObject> debugSphere =
		Engine::MeshObject::CreateMeshObject("Arena/DebugSphereForClass.mesh", "defaultDebugShapes.mat");
	debugSphere->EnableDebugging(true);
	debugSphere->getMaterial()->changeMaterialColor(iColor.r, iColor.g, iColor.b);
	Math::cVector tempPosition;
	tempPosition.x = iCenter.x;
	tempPosition.y = iCenter.y;
	tempPosition.z = iCenter.z;
	debugSphere->setTransformation(tempPosition, Engine::Math::cQuaternion());
	Engine::Scene::getRenderableScene()->addObjectToScene(debugSphere);
}

//Box
void Engine::Debug::DrawShape(ShapeTarget iShapeType,
	Engine::Maths::Point3 i_position,
	float iLength,
	float iWidth,
	float iHeight,
	Engine::Graphics::RGBColor iColor)
{
	WindowsUtil::Assert(iShapeType == BOX, "Shape Type is Not Box");
	Engine::Graphics::RGBAColor color;
	color.r = iColor.r;
	color.g = iColor.g;
	color.b = iColor.b;
	color.a = 1.0f;
	Engine::SharedPointer<Engine::MeshObject> debugBox =
		Engine::MeshObject::CreateMeshObject("Arena/DebugCubeForClass.mesh", "defaultDebugShapes.mat");
	debugBox->EnableDebugging(true);
	debugBox->getMaterial()->changeMaterialColor(iColor.r, iColor.g, iColor.b);
	Math::cVector tempPosition;
	tempPosition.x = i_position.x;
	tempPosition.y = i_position.y;
	tempPosition.z = i_position.z;
	debugBox->setTransformation(tempPosition, Engine::Math::cQuaternion());
	Engine::Scene::getRenderableScene()->addObjectToScene(debugBox);
}

//Cylinder
void Engine::Debug::DrawShape(ShapeTarget iShapeType,
	Engine::Maths::Point3 i_position,
	float iRadius,
	float iHeight,
	Engine::Graphics::RGBColor iColor)
{
	WindowsUtil::Assert(iShapeType == CYLINDER, "Shape Type is Not Cylinder");
	Engine::Graphics::RGBAColor color;
	color.r = iColor.r;
	color.g = iColor.g;
	color.b = iColor.b;
	color.a = 1.0f;
	Engine::SharedPointer<Engine::MeshObject> debugCylinder =
		Engine::MeshObject::CreateMeshObject("Arena/DebugCylinderForClass.mesh", "defaultDebugShapes.mat");
	debugCylinder->EnableDebugging(true);
	debugCylinder->getMaterial()->changeMaterialColor(iColor.r, iColor.g, iColor.b);
	Math::cVector tempPosition;
	tempPosition.x = i_position.x;
	tempPosition.y = i_position.y;
	tempPosition.z = i_position.z;
	debugCylinder->setTransformation(tempPosition, Engine::Math::cQuaternion());
	Engine::Scene::getRenderableScene()->addObjectToScene(debugCylinder);
}




