#include "DebugShapes.h"
#include "../../Windows/WindowsFunctions.h"
#include "../../Graphics/Line.h"
#include "../EngineCore/Objects/Scene.h"
#include "../EngineCore/EngineCore.h"


std::vector<Engine::SharedPointer<Engine::Object>> Engine::Debug::debugShapeList;

bool Engine::Debug::IsDebugShapesAvailable()
{
	return (debugShapeList.size() > 0 ? true: false);
}


//Line
void Engine::Debug::DrawShape(ShapeTarget i_shapeType,
	Engine::Math::Vector3 iStartPoint,
	Engine::Math::Vector3 iEndPoint,
	Engine::Graphics::RGBColor iColor)
{
	WindowsUtil::Assert(i_shapeType == LINE, "Shape Type is Not Line");
	Engine::Graphics::RGBAColor color;
	color.r = iColor.r;
	color.g = iColor.g;
	color.b = iColor.b;
	color.a = 1.0f;
	
	if (Engine::Graphics::Line::getLineCounts() == 0)
	{
		std::string materialFolderName = EngineCore::getMaterialFolderPath();
		materialFolderName += "Game/lineMaterial.mat";
		Engine::Graphics::Material::addMaterialToList(materialFolderName.c_str());
		Engine::Graphics::Line::setMaterialName(materialFolderName);
	}	
	Engine::Graphics::Line::AddLine(
		iStartPoint, iEndPoint, color);
}

//Sphere
void Engine::Debug::DrawShape(ShapeTarget iShapeType,
	Engine::Math::Vector3 iCenter,
	float iRadius,
	Engine::Graphics::RGBColor iColor)
{
	WindowsUtil::Assert(iShapeType == SPHERE, "Shape Type is Not Sphere");
	Engine::Graphics::RGBAColor color;
	color.r = iColor.r;
	color.g = iColor.g;
	color.b = iColor.b;
	color.a = 1.0f;
	Engine::SharedPointer<Engine::MeshObject> debugSphere =
		Engine::MeshObject::CreateMeshObject("Game/DebugSphereForClass.mesh", "Game/defaultDebugShapes.mat", color);
	debugSphere->EnableDebugging(true);
	debugSphere->getMaterial()->changeMaterialColor(iColor.r, iColor.g, iColor.b);
	Math::Vector3 tempPosition;
	tempPosition.x = iCenter.x;
	tempPosition.y = iCenter.y;
	tempPosition.z = iCenter.z;
	debugSphere->setTransform(tempPosition, Engine::Math::Quaternion());
	Engine::Scene::getRenderableScene()->addObjectToScene(debugSphere);
}

//Box
void Engine::Debug::DrawShape(ShapeTarget iShapeType,
	Engine::Math::Vector3 i_position,
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
		Engine::MeshObject::CreateMeshObject("Game/DebugCubeForClass.mesh", 
			"Game/defaultDebugShapes.mat", color);
	debugBox->EnableDebugging(true);
	debugBox->getMaterial()->changeMaterialColor(iColor.r, iColor.g, iColor.b);
	Math::Vector3 tempPosition;
	tempPosition.x = i_position.x;
	tempPosition.y = i_position.y;
	tempPosition.z = i_position.z;
	debugBox->setTransform(tempPosition, Engine::Math::Quaternion());
	Engine::Scene::getRenderableScene()->addObjectToScene(debugBox);
}

//Cylinder
void Engine::Debug::DrawShape(ShapeTarget iShapeType,
	Engine::Math::Vector3 i_position,
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
		Engine::MeshObject::CreateMeshObject("Game/DebugCylinderForClass.mesh", "Game/defaultDebugShapes.mat", color);
	debugCylinder->EnableDebugging(true);
	debugCylinder->getMaterial()->changeMaterialColor(iColor.r, iColor.g, iColor.b);
	Math::Vector3 tempPosition;
	tempPosition.x = i_position.x;
	tempPosition.y = i_position.y;
	tempPosition.z = i_position.z;
	debugCylinder->setTransform(tempPosition, Engine::Math::Quaternion());
	Engine::Scene::getRenderableScene()->addObjectToScene(debugCylinder);
}




