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
	Engine::utils::StringHash temp(Engine::EngineCore::getStringPool()->findString("UpdateObject"));
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
	mTransform = Math::Transform();
	mInitialTransform = Math::Transform();
	mMeshName = i_meshName;
	mMaterial = i_materialName;
	mObjectController = nullptr;
	debugObject = false;
	vertexModifierUniform = "vertexColorModifier\0";
	isInitialTransform = true;
	scaleFactor = Math::Vector3(1.0, 1.0, 1.0);
	isPlayer = false;
	mObjectType = ObjectType::NONE;
	isSSAO = false;
}

Engine::MeshObject::MeshObject()
{
	renderable = true;
	mMeshName = "";
	mMaterial = "";
	mObjectController = nullptr;
	mTransform.setOrientation(Engine::Math::Quaternion());
	mTransform.setPosition(Engine::Math::Vector3());
	debugObject = false;
	isInitialTransform = true;
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
	if (i_objectController)
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

void Engine::MeshObject::setTransform(Engine::Math::Vector3 i_positionOffset, Engine::Math::Quaternion i_orientation)
{
	mTransform.setOrientation(i_orientation);
	mTransform.setPosition(i_positionOffset);
	if(isInitialTransform)
	{
		mInitialTransform = mTransform;
		isInitialTransform = false;
	}
}

void Engine::MeshObject::resetTransform()
{
	mTransform = mInitialTransform;
}


void Engine::MeshObject::HandleMessage(Engine::utils::StringHash& i_message, RTTI* i_MessageSender, void* i_pMessageData)
{
	if (i_MessageSender != nullptr)
	{
		if (i_MessageSender != nullptr && Engine::utils::StringHash("UpdateObject") == i_message && mObjectController)
			mObjectController->updateObject(*this, *reinterpret_cast<Engine::typedefs::ActionWithKeyBound*>(i_pMessageData));		
	}
}


void Engine::MeshObject::updateObject()
{
	typedefs::ActionWithKeyBound action;
	action.action = typedefs::Default;
	action.keyVal = 0x00;
	if(mObjectController)
		mObjectController->updateObject(*this, action);
}


void Engine::MeshObject::setScale(float x, float y, float z)
{
	scaleFactor = Math::Vector3(x, y, z);
}



Engine::Math::Transform Engine::MeshObject::getTransform()
{
	return mTransform;
}

Engine::MeshObject::~MeshObject()
{
	if (mObjectController)
		delete mObjectController;
}

void Engine::MeshObject::draw(bool drawDebugObject)
{
	if (renderable && (drawDebugObject && debugObject || !debugObject))
	{
		SharedPointer<Scene> activeScene = Scene::getRenderableScene();
		SharedPointer<Camera> tempCamera = activeScene->getActiveCamera();
		Engine::SharedPointer<Graphics::Material> tempMaterial =
			Engine::Graphics::Material::getMaterial(mMaterial.c_str());
		WindowsUtil::Assert(!tempMaterial.isNull(), "Material for the skybox is not available");
		Scene::applyPaintersAlgorithmForTransparency();
		if (!tempCamera.isNull())
		{
			Math::Transform cameraTransform = tempCamera->getTransform();
			float fieldOfView = tempCamera->getFieldOfView();
			float aspectRatio = tempCamera->getAspectRatio();
			float nearPlane = tempCamera->getNearPlane();
			float farPlane = tempCamera->getFarPlane();
			if (debugObject)
				Engine::Graphics::GraphicsSystem::EnableWireFrame(true);
			getEffect()->setShaders();
			Math::Transform gameObjectTransform = getTransform();
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

			SharedPointer<Graphics::Uniform> scaleMatrix = Graphics::Uniform::getUniform(
				getEffect()->getTransformMatrixUniformName(
					Graphics::Vertex,
					Graphics::ScaleMatrix), tempMaterial->getEffectName(), Graphics::Vertex);

			SharedPointer<Graphics::Uniform> normalMatrix = Graphics::Uniform::getUniform(
				getEffect()->getTransformMatrixUniformName(
					Graphics::Vertex,
					Graphics::NormalMatrix), tempMaterial->getEffectName(), Graphics::Vertex);
			
			if (!localToWorldUniform.isNull())
			{
				Graphics::UniformValues localToWorlValues;
				localToWorlValues.matrixValue.Type = Graphics::LocalToWorld;
				localToWorlValues.matrixValue.matrix =
					Math::Matrix4x4(mTransform.getOrientation(),
						mTransform.getPosition());
				localToWorldUniform->setUniformValue(localToWorlValues);
			}

			if (!worldToView.isNull())
			{
				Graphics::UniformValues worldToViewValues;
				worldToViewValues.matrixValue.Type = Graphics::WorldToView;
				worldToViewValues.matrixValue.matrix =
					Math::Matrix4x4::CreateWorldToViewTransform(
						cameraTransform.getOrientation(),
						cameraTransform.getPosition());
				worldToView->setUniformValue(worldToViewValues);
			}

			if (!scaleMatrix.isNull())
			{
				Graphics::UniformValues scaleMatrixValues;
				scaleMatrixValues.matrixValue.Type = Graphics::ScaleMatrix;
				scaleMatrixValues.matrixValue.matrix = Engine::Math::Matrix4x4::CreateScaleMatrix(
					scaleFactor);
				scaleMatrix->setUniformValue(scaleMatrixValues);
			}

			if (!normalMatrix.isNull())
			{
				Graphics::UniformValues normalMatrixValues;
				normalMatrixValues.matrixValue.Type = Graphics::NormalMatrix;
				normalMatrixValues.matrixValue.matrix = Engine::Math::Matrix4x4::CreateNormalMatrix(
					Math::Matrix4x4(mTransform.getOrientation(), mTransform.getPosition()));
				normalMatrix->setUniformValue(normalMatrixValues);
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
				= Engine::Graphics::Uniform::getUniform(vertexModifierUniform, 
					effectFile, Graphics::Vertex);
			vertexColorUiform->setUniformValue(tempColor);
			

			Engine::Graphics::Uniform::setAllUniformToShaderObjects(effectFile);
			Engine::Graphics::UniformBlock::setAllUniformBlockForTheEffectInShader(effectFile);

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


void Engine::MeshObject::castShadow(bool, Graphics::ShadowMethod)
{
	//To do	
}


bool Engine::MeshObject::castingShadowEnabled()
{
	//to do 
	return true;
}

void Engine::MeshObject::enablePhysics(bool)
{
	//To do
}


void Engine::MeshObject::receiveShadow(bool)
{
	//To do
}

bool Engine::MeshObject::receivingShadowEnabled()
{
	//to do
	return false;
}


bool Engine::MeshObject::isCollidable()
{
	//To do
	return false;
}

bool Engine::MeshObject::isPhysicsEnabled()
{
	//to do
	return false;
}

void Engine::MeshObject::enableCollision(bool)
{
	//to do
}


bool Engine::MeshObject::IsPlayer()
{
	return isPlayer;
}

void Engine::MeshObject::setPlayer(bool i_isPlayer)
{
	isPlayer = i_isPlayer;
}


Engine::ObjectType Engine::MeshObject::getObjectType()
{
	return mObjectType;
}

void Engine::MeshObject::setObjectType(ObjectType iObjectType)
{
	mObjectType = iObjectType;
}

Engine::Graphics::RGBAColor Engine::MeshObject::GetVertexColor() const
{
	return vertexColor;
}

void Engine::MeshObject::SetMaterial(std::string iMaterialName)
{
	mMaterial = iMaterialName;
}


void Engine::MeshObject::EnableSSAO(bool iRequest)
{
	isSSAO = iRequest;
}


bool Engine::MeshObject::isSSAOEnabled()
{
	return isSSAO;
}
















