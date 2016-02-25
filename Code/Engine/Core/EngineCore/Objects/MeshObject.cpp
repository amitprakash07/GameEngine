#include "MeshObject.h"
#include "../../../Core/Utilities/HashedString.h"
#include "../../../Windows/WindowsFunctions.h"
#include "../../../Core/EngineCore/EngineCore.h"
#include "Scene.h"
#include  "../../../Graphics/Graphics.h"
#include "../../../Graphics/Uniform.h"
#include <iostream>


Engine::SharedPointer<Engine::MeshObject> Engine::MeshObject::CreateMeshObject(
	std::string i_meshFileName, 
	std::string i_materialName,
	Engine::Graphics::RGBAColor iColor)
{
	i_meshFileName = Engine::EngineCore::getMeshFolderPath() + i_meshFileName;
	i_materialName = Engine::EngineCore::getMaterialFolderPath() + i_materialName;
	SharedPointer<MeshObject> tempMeshObject(new MeshObject(i_meshFileName, i_materialName), "Engine::MeshObject");
	Engine::utils::StringHash temp(Engine::EngineCore::getStringPool()->findString("UpdateMeshObject"));
	Engine::EngineCore::getMessagingSystem()->addMessageHandler(temp, reinterpret_cast<IMessageHandler*>(tempMeshObject.getRawPointer()), Engine::typedefs::HIGH);

	if (!i_meshFileName.empty() && !i_meshFileName.empty() && !i_materialName.empty())
	{
		std::stringstream errormessage;

		if (!Engine::Graphics::Material::addMaterialToList(i_materialName.c_str()))
		{
			errormessage << "Unable to Load Effect";
			MessageBox(nullptr, errormessage.str().c_str(), nullptr, MB_OK);
			tempMeshObject.deleteObject();
			return (SharedPointer<MeshObject>());
		}

		if (!Engine::Graphics::Mesh::addToMeshList(i_meshFileName))
		{
			errormessage << "Unable to Load Mesh";
			MessageBox(nullptr, errormessage.str().c_str(), nullptr, MB_OK);
			tempMeshObject.deleteObject();
			return (SharedPointer<MeshObject>());
		}

		//VertexColorModifier Uniform - Change here if changing the of the color;
		SharedPointer<Engine::Graphics::Uniform> colorUniform = 
			Engine::Graphics::Uniform::addUniform(tempMeshObject->vertexModifierUniform, 
				tempMeshObject->getMaterial()->getEffectName(), 
				Graphics::Vertex);
		colorUniform->setValType(Graphics::Vector);
		colorUniform->setValCount(1);
		tempMeshObject->vertexColor = iColor;
		std::string tempUniformName = tempMeshObject->vertexModifierUniform;		
		colorUniform->setHandle(
		tempMeshObject->getEffect()->Engine::Graphics::Effect::getUniformHandle(
			tempUniformName.c_str(), Graphics::Vertex));
		
	}
	return tempMeshObject;
}

Engine::MeshObject::MeshObject(std::string i_meshName, std::string i_materialName)
{
	renderable = true;
	mTransformation = Math::Transformation();
	mMeshName = i_meshName;
	mMaterial = i_materialName;
	mObjectController = nullptr;
	debugObject = false;
	vertexModifierUniform = "vertexColorModifier\0";
}

Engine::MeshObject::MeshObject()
{
	renderable = true;
	mMeshName = "";
	mMaterial = "";
	mObjectController = nullptr;
	mTransformation.mOrientation = Engine::Math::Quaternion();
	mTransformation.mPositionOffset = Engine::Math::Vector3();
	debugObject = false;
}

void Engine::MeshObject::EnableDebugging(bool enable)
{
	debugObject = enable;
}

bool Engine::MeshObject::isDebugObject() const
{
	return debugObject;
}

void Engine::MeshObject::setObjectController(IObjectController* i_objectController)
{
	mObjectController = i_objectController;
}


Engine::SharedPointer<Engine::Graphics::Mesh> Engine::MeshObject::getMesh() const
{
	return Engine::Graphics::Mesh::getMesh(mMeshName);
}

Engine::SharedPointer<Engine::Graphics::Effect> Engine::MeshObject::getEffect() const
{
	return Engine::Graphics::Effect::getEffect(Engine::Graphics::Material::getMaterial(mMaterial.c_str())->getEffectName());
}

Engine::SharedPointer<Engine::Graphics::Material> Engine::MeshObject::getMaterial() const
{
	return Engine::Graphics::Material::getMaterial(mMaterial.c_str());
}

bool Engine::MeshObject::isRenderable() const
{
	return renderable;
}

void Engine::MeshObject::setTransformation(Engine::Math::Vector3 i_positionOffset, Engine::Math::Quaternion i_orientation)
{
	mTransformation.mOrientation = i_orientation;
	mTransformation.mPositionOffset = i_positionOffset;
}

void Engine::MeshObject::HandleMessage(Engine::utils::StringHash& i_message, RTTI* i_MessageSender, void* i_pMessageData)
{
	if (i_MessageSender != nullptr)
	{
		//if (/*isBothSameType(i_MessageSender, Engine::InputController::getInputController()->getTypeInfo()) && (*/Engine::utils::StringHash("UpdateMeshObject") == i_message)//)
		//{
		//	//Engine::SharedPointer<Engine::MeshObject> temp= SharedPointer<MeshObject>(this); //Need to think about this
		//	switch (*(reinterpret_cast<Engine::typedefs::Direction*>(i_pMessageData)))
		//	{
		//	case Engine::typedefs::NONE:
		//		break;
		//	case Engine::typedefs::UP:
		//		if (mObjectController)
		//			mObjectController->updateObject(*this, Engine::typedefs::UP);
		//		break;
		//	case Engine::typedefs::DOWN:
		//		if (mObjectController)
		//			mObjectController->updateObject(*this, Engine::typedefs::DOWN);
		//		break;
		//	case Engine::typedefs::LEFT:
		//		if (mObjectController)
		//			mObjectController->updateObject(*this, Engine::typedefs::LEFT);
		//		break;
		//	case Engine::typedefs::RIGHT:
		//		if (mObjectController)
		//			mObjectController->updateObject(*this, Engine::typedefs::RIGHT);
		//		break;
		//	}
		//}
	}
}

Engine::Math::Transformation Engine::MeshObject::getTransformation()
{
	return mTransformation;
}

Engine::MeshObject::~MeshObject()
{
	if (mObjectController)
		delete mObjectController;
}

void Engine::MeshObject::draw(bool drawDebugObject)
{
	if (drawDebugObject && debugObject || !debugObject)
	{
		SharedPointer<Scene> activeScene = Scene::getRenderableScene();
		SharedPointer<Camera> tempCamera = activeScene->getActiveCamera();
		Scene::applyPaintersAlgorithmForTransparency();
		if (!tempCamera.isNull())
		{
			Math::Transformation cameraTransformation = tempCamera->getTransformation();
			float fieldOfView = tempCamera->getFieldOfView();
			float aspectRatio = tempCamera->getAspectRatio();
			float nearPlane = tempCamera->getNearPlane();
			float farPlane = tempCamera->getFarPlane();
			if (debugObject)
				Engine::Graphics::GraphicsSystem::EnableWireFrame(true);
			getEffect()->setShaders();
			Math::Transformation gameObjectTransformation = getTransformation();
			std::string effectFile = getMaterial()->getEffectName();

			SharedPointer<Graphics::Uniform> localToWorldUniform = 
				Graphics::Uniform::getUniform(
					getEffect()->getTransformMatrixUniformName(
						Graphics::Vertex,
						Graphics::LocalToWorld), effectFile, Graphics::Vertex);

			SharedPointer<Graphics::Uniform> worldToView = Graphics::Uniform::getUniform(
				getEffect()->getTransformMatrixUniformName(
					Graphics::Vertex,
					Graphics::WorldToView), effectFile, Graphics::Vertex);

			SharedPointer<Graphics::Uniform> viewToScreen = Graphics::Uniform::getUniform(
				getEffect()->getTransformMatrixUniformName(
					Graphics::Vertex,
					Graphics::ViewToScreen), effectFile, Graphics::Vertex);
			
			if (!localToWorldUniform.isNull())
			{
				Graphics::UniformValues localToWorlValues;
				localToWorlValues.matrixValue.Type = Graphics::LocalToWorld;
				localToWorlValues.matrixValue.matrix =
					Math::Matrix4x4(mTransformation.mOrientation,
						mTransformation.mPositionOffset);
				localToWorldUniform->setUniformValue(localToWorlValues);
			}

			if (!worldToView.isNull())
			{
				Graphics::UniformValues worldToViewValues;
				worldToViewValues.matrixValue.Type = Graphics::WorldToView;
				worldToViewValues.matrixValue.matrix =
					Math::Matrix4x4::CreateWorldToViewTransform(
						cameraTransformation.mOrientation,
						cameraTransformation.mPositionOffset);
				worldToView->setUniformValue(worldToViewValues);
			}

			if (!viewToScreen.isNull())
			{
				Graphics::UniformValues viewToScreenValues;
				viewToScreenValues.matrixValue.Type = Graphics::ViewToScreen;
				viewToScreenValues.matrixValue.matrix =
					Math::Matrix4x4::CreateViewToScreenTransform(
						fieldOfView, aspectRatio,
						nearPlane, farPlane);
				viewToScreen->setUniformValue(viewToScreenValues);
			}


			Engine::Graphics::UniformValues tempColor;
			
			tempColor.vectorValue.x = vertexColor.r;
			tempColor.vectorValue.y = vertexColor.g;
			tempColor.vectorValue.z = vertexColor.b;
			tempColor.vectorValue.w = vertexColor.a;

			SharedPointer<Engine::Graphics::Uniform> vertexColorUiform
				= Engine::Graphics::Uniform::getUniform(vertexModifierUniform, effectFile, Graphics::Vertex);
			vertexColorUiform->setUniformValue(tempColor);
			

			Engine::Graphics::Uniform::setAllUniformToShaderObjects(effectFile);
			getMaterial()->setMaterialUniformParameters();
			getMaterial()->setTextureUniform();
			getMesh()->drawMesh();
			if (debugObject)
				Engine::Graphics::GraphicsSystem::EnableWireFrame(false);
		}
		else
		{
			std::stringstream errormessage;
			errormessage << "Camera is not iniitalized\n";
			WindowsUtil::Print(errormessage.str().c_str());
			return;
		}
	}
}