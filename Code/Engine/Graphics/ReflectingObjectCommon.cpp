#include "ReflectingObject.h"
#include "../Core/EngineCore/EngineCore.h"
#include "Material.h"
#include "Mesh.h"
#include <sstream>
#include "../Core/Utilities/IObjectController.h"


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
		tempReflectingObject->textureName = "dynamic" + i_meshFileName;
		tempReflectingObject->cubeMapGenerated = false;

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

		SharedPointer<Engine::Graphics::Uniform> colorUniform =
			Engine::Graphics::Uniform::addUniform("vertexColorModifier",
				Engine::Graphics::Material::getMaterial(
					tempReflectingObject->materialName.c_str())->getEffectName(),
				Graphics::Vertex);

		colorUniform->setValType(Graphics::Vector);
		colorUniform->setValCount(1);
		std::string tempUniformName = "vertexColorModifier";
		colorUniform->setHandle(
			Engine::Graphics::Effect::getEffect(
				Engine::Graphics::Material::getMaterial(
					tempReflectingObject->materialName.c_str())->getEffectName())->getUniformHandle(
				tempUniformName.c_str(), Graphics::Vertex));
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
	if(isInitialTransform)
	{
		isInitialTransform = false;
		mInitialTransform = mTransform;
	}
}

void Engine::Graphics::ReflectingObject::resetTransform()
{
	mTransform = mInitialTransform;
}


void Engine::Graphics::ReflectingObject::setDynamicTextureSamplerName(
	std::string samplerUniformName)
{
	dynamicTextureSamplerName = samplerUniformName;
}


void Engine::Graphics::ReflectingObject::setObjectController(SharedPointer<IObjectController>i_objectController)
{
	if (!i_objectController.isNull())
		mObjectController = i_objectController;
}


void Engine::Graphics::ReflectingObject::updateObject()
{
	typedefs::ActionWithKeyBound action;
	action.action = typedefs::Default;
	action.keyVal = 0x00;
	if (!mObjectController.isNull())
		mObjectController->updateObject(*this, action);
}


void Engine::Graphics::ReflectingObject::setScale(float x, float y, float z)
{
	scaleFactor = Math::Vector3(x, y, z);
}


void Engine::Graphics::ReflectingObject::castShadow(bool, Graphics::ShadowMethod)
{
	//To Do
}

bool Engine::Graphics::ReflectingObject::castingShadowEnabled()
{
	//To Do
	return false;
}


bool Engine::Graphics::ReflectingObject::isPhysicsEnabled()
{
	//To do
	return false;
}

void Engine::Graphics::ReflectingObject::receiveShadow(bool)
{
	//To do
}

bool Engine::Graphics::ReflectingObject::receivingShadowEnabled()
{
	//To do
	return false;
}

void Engine::Graphics::ReflectingObject::enableCollision(bool)
{
	//To Do	
}

void Engine::Graphics::ReflectingObject::enablePhysics(bool)
{
	//to Do
}


bool Engine::Graphics::ReflectingObject::isCollidable()
{
	//to Do
	return false;
}


bool Engine::Graphics::ReflectingObject::IsPlayer()
{
	return isPlayer;
}


void Engine::Graphics::ReflectingObject::setPlayer(bool i_isPlayer)
{
	isPlayer = i_isPlayer;
}


void Engine::Graphics::ReflectingObject::setObjectType(ObjectType iObjectType)
{
	mObjectType = iObjectType;
}


Engine::ObjectType Engine::Graphics::ReflectingObject::getObjectType()
{
	return mObjectType;
}

void Engine::Graphics::ReflectingObject::SetMaterial(std::string iMaterialName)
{
	materialName = iMaterialName;
}




















