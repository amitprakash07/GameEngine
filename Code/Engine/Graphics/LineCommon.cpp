#include "../Windows/WindowsFunctions.h"
#include "../Core/EngineCore/EngineCore.h"
#include "Material.h"
#include "Effect.h"
#include "../Core/EngineCore/Objects/Scene.h"


std::vector<Engine::SharedPointer<Engine::Graphics::Line>>
Engine::Graphics::Line::mLineList;
std::string Engine::Graphics::Line::materialName;
bool Engine::Graphics::Line::bufferInitialized;
bool Engine::Graphics::Line::vertexBufferInitalized;


Engine::Graphics::Line::Line()
{
	debugObject = true;
	bufferInitialized = false;
	vertexBufferInitalized = false;	
	mObjectType = ObjectType::NONE;
}

bool Engine::Graphics::Line::containsDebugLine()
{
	return mLineList.size() > 0 ? true : false;
}


Engine::SharedPointer<Engine::Graphics::Line> 
		Engine::Graphics::Line::AddLine(
			Engine::Math::Vector3 i_startPoint, 
			Engine::Math::Vector3 i_endPoint, 
			RGBAColor iLineColor)
{
	SharedPointer<Line> tempLine = SharedPointer<Line>(new Line(), "Engine::Graphics::Line");
	tempLine->mLineStruct.startPoint = i_startPoint;
	tempLine->mLineStruct.endPoint = i_endPoint;
	tempLine->mLineStruct.color = iLineColor;
	tempLine->debugObject = true;
	mLineList.push_back(tempLine);
	createBuffer();
	return tempLine;	
}

Engine::Math::Transform Engine::Graphics::Line::getTransform()
{
	return Math::Transform();
}

void Engine::Graphics::Line::setTransform(Math::Vector3, Math::Quaternion)
{}

void Engine::Graphics::Line::resetTransform()
{
	
}



bool Engine::Graphics::Line::isDebugObject() const
{
	return debugObject;
}


bool Engine::Graphics::Line::isRenderable() const
{
	return true;
}


void Engine::Graphics::Line::draw(bool drawDebugObject)
{
	/*drawLines(drawDebugObject);*/
}

void Engine::Graphics::Line::setMaterialName(std::string iMaterialName)
{
	materialName = iMaterialName;
}

uint8_t Engine::Graphics::Line::getLineCounts()
{
	return static_cast<uint8_t>(mLineList.size());
}


bool Engine::Graphics::Line::setUniforms()
{
	SharedPointer<Scene> activeScene = Scene::getRenderableScene();
	SharedPointer<Camera> tempCamera = activeScene->getActiveCamera();

	if (!tempCamera.isNull())
	{
		Math::Transform cameraTransform = tempCamera->getTransform();
		float fieldOfView = tempCamera->getFieldOfView();
		float aspectRatio = tempCamera->getAspectRatio();
		float nearPlane = tempCamera->getNearPlane();
		float farPlane = tempCamera->getFarPlane();

		std::string effectFile =
			Engine::Graphics::Material::getMaterial(materialName.c_str())->getEffectName();

		SharedPointer<Graphics::Uniform> worldToView = Graphics::Uniform::getUniform(
			Engine::Graphics::Effect::getEffect(effectFile)->getTransformMatrixUniformName(
				Graphics::Vertex,
				Graphics::WorldToView), effectFile, Graphics::Vertex);

		SharedPointer<Graphics::Uniform> viewToScreen = Graphics::Uniform::getUniform(
			Engine::Graphics::Effect::getEffect(effectFile)->getTransformMatrixUniformName(
				Graphics::Vertex,
				Graphics::ViewToScreen), effectFile, Graphics::Vertex);

		Graphics::UniformValues worldToViewValues;
		worldToViewValues.matrixValue.Type = Graphics::WorldToView;
		worldToViewValues.matrixValue.matrix =
			Math::Matrix4x4::CreateWorldToViewTransform(
				cameraTransform.getOrientation(),
				cameraTransform.getPosition());
		worldToView->setUniformValue(worldToViewValues);


		Graphics::UniformValues viewToScreenValues;
		viewToScreenValues.matrixValue.Type = Graphics::ViewToScreen;
		viewToScreenValues.matrixValue.matrix =
			Math::Matrix4x4::CreateViewToScreenTransform(
				fieldOfView, aspectRatio,
				nearPlane, farPlane);
		viewToScreen->setUniformValue(viewToScreenValues);

		Engine::Graphics::Uniform::setAllUniformToShaderObjects(effectFile);
	}
	else
	{
		std::stringstream errormessage;
		errormessage << "Camera is not iniitalized\n";
		WindowsUtil::Print(errormessage.str().c_str());
		return false;
	}
	return true;
}


void Engine::Graphics::Line::updateObject()
{
	typedefs::ActionWithKeyBound action;
	action.action = typedefs::Default;
	action.keyVal = 0x00;
	if (!mObjectController.isNull())
		mObjectController->updateObject(*this, action);
}


void Engine::Graphics::Line::setObjectController(SharedPointer<IObjectController>i_ObjectControlller)
{
	if (!i_ObjectControlller.isNull())
		mObjectController = i_ObjectControlller;
}


void Engine::Graphics::Line::castShadow(bool, Graphics::ShadowMethod)
{
	//To do Stub
}

bool Engine::Graphics::Line::castingShadowEnabled()
{
	//To do
	return false;
}

void Engine::Graphics::Line::enablePhysics(bool)
{
	//To do
}

void Engine::Graphics::Line::receiveShadow(bool)
{
	//To do
}

bool Engine::Graphics::Line::receivingShadowEnabled()
{
	//To do
	return false;
}

bool Engine::Graphics::Line::isCollidable()
{
	//to do 
	return false;
}

bool Engine::Graphics::Line::isPhysicsEnabled()
{
	//To do 
	return false;
}


void Engine::Graphics::Line::enableCollision(bool)
{
	//To do - stub
}


void Engine::Graphics::Line::setObjectType(ObjectType iObjectType)
{
	mObjectType = iObjectType;
}

Engine::ObjectType Engine::Graphics::Line::getObjectType()
{
	return mObjectType;
}

void Engine::Graphics::Line::SetMaterial(std::string iMaterialName)
{
	materialName = iMaterialName;
}
























