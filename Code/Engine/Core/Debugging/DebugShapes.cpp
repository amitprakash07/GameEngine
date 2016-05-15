#include "DebugShapes.h"
#include "../../Windows/WindowsFunctions.h"
#include "../../Graphics/Line.h"
#include "../EngineCore/Objects/Scene.h"
#include "../EngineCore/EngineCore.h"


std::map<Engine::ShapeTarget, std::map<std::string, 
	Engine::SharedPointer<Engine::Object>>>
	Engine::Debug::DebugShapes::debugShapeList;

bool Engine::Debug::DebugShapes::IsDebugShapesAvailable()
{
	return (debugShapeList.size() > 0 ? true: false);
}

//Line
Engine::SharedPointer<Engine::Graphics::Line> 
	Engine::Debug::DebugShapes::DrawShape(
	std::string iName,
	ShapeTarget i_shapeType,
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

	return Engine::Graphics::Line::AddLine(
		iStartPoint, iEndPoint, color);	
}

//Sphere
Engine::SharedPointer<Engine::MeshObject> Engine::Debug::DebugShapes::DrawShape(
	std::string iName,
	ShapeTarget iShapeType,
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
		Engine::MeshObject::CreateMeshObject("Game/DebugSphereForClass.mesh", 
			"Game/defaultDebugShapes.mat", color);
	debugSphere->EnableDebugging(true);
	debugSphere->getMaterial()->changeMaterialColor(iColor.r, iColor.g, iColor.b);
	Math::Vector3 tempPosition;
	tempPosition.x = iCenter.x;
	tempPosition.y = iCenter.y;
	tempPosition.z = iCenter.z;
	debugSphere->setTransform(tempPosition, Engine::Math::Quaternion());
	Engine::Scene::getRenderableScene()->addObjectToScene(debugSphere);

	SharedPointer<Object> tempObject = debugSphere.CastSharedPointer<Object>();
	debugShapeList[iShapeType][iName] = tempObject;
	return debugSphere;
}

//Box
Engine::SharedPointer<Engine::MeshObject> Engine::Debug::DebugShapes::DrawShape(
	std::string iName,
	ShapeTarget iShapeType,
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

	SharedPointer<Object> tempObject = debugBox.CastSharedPointer<Object>();
	debugShapeList[iShapeType][iName] = tempObject;
	return debugBox;
}

//Cylinder
Engine::SharedPointer<Engine::MeshObject> Engine::Debug::DebugShapes::DrawShape(
	std::string iName,
	ShapeTarget iShapeType,
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
		Engine::MeshObject::CreateMeshObject("Game/DebugCylinderForClass.mesh", 
			"Game/defaultDebugShapes.mat", color);
	debugCylinder->EnableDebugging(true);
	debugCylinder->getMaterial()->changeMaterialColor(iColor.r, iColor.g, iColor.b);
	Math::Vector3 tempPosition;
	tempPosition.x = i_position.x;
	tempPosition.y = i_position.y;
	tempPosition.z = i_position.z;
	debugCylinder->setTransform(tempPosition, Engine::Math::Quaternion());
	Engine::Scene::getRenderableScene()->addObjectToScene(debugCylinder);

	SharedPointer<Object> tempObject = debugCylinder.CastSharedPointer<Object>();
	debugShapeList[iShapeType][iName] = tempObject;
	return debugCylinder;
}


Engine::SharedPointer<Engine::Object> Engine::Debug::DebugShapes::GetDebugShape(
	std::string iName,
	ShapeTarget iShape)
{
	for(std::map<ShapeTarget, std::map<std::string, SharedPointer<Object>>>::iterator i = debugShapeList.begin();
		i!=debugShapeList.end(); ++i)
	{
		if (i->first == iShape)
		{
			for (std::map<std::string, SharedPointer<Object>>::iterator j = i->second.begin();
				j != i->second.end(); ++j)
			{
				if (j->first == iName)
					return j->second;
			}
		}
	}
	return SharedPointer<Object>();
}



