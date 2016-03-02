#include "ReflectingObject.h"
#include "../Core/EngineCore/EngineCore.h"
#include "Material.h"
#include "Mesh.h"
#include <sstream>

Engine::SharedPointer<Engine::Graphics::ReflectingObject> 
	Engine::Graphics::ReflectingObject::CreateReflectingObject(
		std::string i_meshFileName,
		std::string i_materialName,
		float nearPlane, 
		float farPlane)
{
	if (!i_meshFileName.empty() & !i_materialName.empty())
	{
		i_meshFileName = Engine::EngineCore::getMeshFolderPath() + i_meshFileName;
		i_materialName = Engine::EngineCore::getMaterialFolderPath() + i_materialName;

		SharedPointer<ReflectingObject> tempReflectingObject(
			new ReflectingObject(), "Engine::Graphics::ReflectingObject");
		tempReflectingObject->meshName = i_meshFileName;
		tempReflectingObject->materialName = i_materialName;

		std::stringstream errormessage;
		if (!Engine::Graphics::Material::addMaterialToList(i_materialName.c_str()))
		{
			errormessage << "Unable to Load Effect";
			MessageBox(nullptr, errormessage.str().c_str(), nullptr, MB_OK);
			tempReflectingObject.deleteObject();
			return (SharedPointer<Engine::Graphics::ReflectingObject>());
		}

		if (!Engine::Graphics::Mesh::addToMeshList(i_meshFileName))
		{
			errormessage << "Unable to Load Mesh";
			MessageBox(nullptr, errormessage.str().c_str(), nullptr, MB_OK);
			tempReflectingObject.deleteObject();
			return (SharedPointer<Engine::Graphics::ReflectingObject>());
		}		
		return tempReflectingObject;		
	}
	return SharedPointer<ReflectingObject>();
}

Engine::Math::Transform Engine::Graphics::ReflectingObject::getTransform()
{
	return mTransform;
}

bool Engine::Graphics::ReflectingObject::isDebugObject() const
{
	return false;
}


bool Engine::Graphics::ReflectingObject::isRenderable() const
{
	return true;
}


void Engine::Graphics::ReflectingObject::setTransform(
	Engine::Math::Vector3 position, 
	Engine::Math::Quaternion rotation)
{
	mTransform.setPosition(position);
	mTransform.setOrientation(rotation);
}





