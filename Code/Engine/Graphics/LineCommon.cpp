#include "Line.h"
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
}

bool Engine::Graphics::Line::containsDebugLine()
{
	return mLineList.size();
}



void Engine::Graphics::Line::AddLine(Engine::Math::Vector3 i_startPoint, Engine::Math::Vector3 i_endPoint, RGBAColor iLineColor)
{
	SharedPointer<Line> tempLine = SharedPointer<Line>(new Line(), "Engine::Graphics::Line");
	tempLine->mLineStruct.startPoint = i_startPoint;
	tempLine->mLineStruct.endPoint = i_endPoint;
	tempLine->mLineStruct.color = iLineColor;
	tempLine->debugObject = true;
	mLineList.push_back(tempLine);
	createBuffer();
}

Engine::Math::Transformation Engine::Graphics::Line::getTransformation()
{
	return Math::Transformation();
}

void Engine::Graphics::Line::setTransformation(Math::Vector3, Math::Quaternion)
{}


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
	return mLineList.size();
}


bool Engine::Graphics::Line::setUniforms()
{
	SharedPointer<Scene> activeScene = Scene::getRenderableScene();
	SharedPointer<Camera> tempCamera = activeScene->getActiveCamera();

	if (!tempCamera.isNull())
	{
		Math::Transformation cameraTransformation = tempCamera->getTransformation();
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
				cameraTransformation.mOrientation,
				cameraTransformation.mPositionOffset);
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









