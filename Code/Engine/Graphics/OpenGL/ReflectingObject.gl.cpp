#include "../ReflectingObject.h"
#include <sstream>
#include "../../../Externals/OpenGLExtensions/OpenGlExtensions.h"
#include "../../../Engine/Core/EngineCore/WindowingSystem/WindowsProgram.h"
#include "../../Windows/WindowsFunctions.h"
#include "../SkyBox.h"
#include "../../Core/Maths/Functions.h"
#include "../../../Engine/Core/Maths/Transform.h"
#include "../../../Engine/Core/Maths/Quaternion.h"
#include "../../../Engine/Core/Maths/Vector3.h"
#include "../Material.h"
#include "../Texture.h"
#include "../../Core/EngineCore/Objects/MeshObject.h"
#include "../Sprite.h"
#include "../Line.h"


namespace Engine
{
	class Scene:public RTTI
	{
	public:
		static Engine::SharedPointer<Scene> getRenderableScene();
		SharedPointer<Camera> getActiveCamera() const;
		bool addCameraToScene(SharedPointer<Camera>&);
		std::vector<SharedPointer<Engine::MeshObject>> getMeshObjectList() const;
		std::vector<SharedPointer<Engine::Graphics::Sprite>> getSpriteObjectList() const;
		std::vector<SharedPointer<Engine::Graphics::Line>> getLineList() const;
	};
}

Engine::Graphics::ReflectingObject::ReflectingObject()	
{
	texture = -1;		
	cubeMapGenerated = false;	
	cameraCreated = false;
	mObjectController = nullptr;
	isInitialTransform = true;
	mInitialTransform = Math::Transform();
	scaleFactor = Math::Vector3(1.0, 1.0, 1.0);
	isPlayer = false;
	mObjectType = ObjectType::NONE;
}


void Engine::Graphics::ReflectingObject::generateCubeMap()
{
	Engine::Math::Transform objectTransform = mTransform;
	std::stringstream errormessage;
	if(init())
	{
		Engine::SharedPointer<Engine::Scene> currentScene =
			Engine::Scene::getRenderableScene();
		Engine::SharedPointer<Engine::Camera> previousCamera =
			currentScene->getActiveCamera();
		previousCamera->activateCamera(false);
		
		Engine::Math::Quaternion rotor =
			Engine::Math::Quaternion::getIdentityQuartenion();

		if (!cameraCreated)
		{
			Engine::SharedPointer<Engine::Camera> tempCamera =
				Engine::Camera::CreateCamera("cubeMapCamera",
					mTransform.getPosition(),
					rotor);
			environmentCamera = tempCamera;
			environmentCamera->setAspectRatio(static_cast<float>(1.0f));
			environmentCamera->setFieldOfView(90.0f);
			currentScene->addCameraToScene(environmentCamera);
			cameraCreated = true;
		}

		environmentCamera->activateCamera(true);		

		GLsizei textureHeight = 2048;
		GLsizei textureWidth = 2048;
		
		Engine::Math::Transform cubeMapCameraTransform = environmentCamera->getTransform();
		for (int i = 5; i >= 0; --i)
		{
			cubeMapCameraTransform.setOrientation(Engine::Math::Quaternion::getIdentityQuartenion());
			switch(i)
			{
			case 5:
				//Negative Z
				rotor = Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(0.0f),
					Engine::Math::Vector3(0.0f, 1.0f, 0.0f));
				break;
			case 4:
				//Positive Z
				//rotor = Engine::Math::Quaternion::getIdentityQuartenion();
				rotor = Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(-180.0f),
					Engine::Math::Vector3(0.0f, 1.0f, 0.0f));
				break;
			case 3:
				//Negative Y
				rotor = Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(-90.0f),
					Engine::Math::Vector3(1.0f, 0.0f, 0.0f));
				break;
			case 2:
				//Positive Y
				rotor = Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(-90.0f),
					Engine::Math::Vector3(1.0f, 0.0f, 0.0f));
				break;
			case 1:
				//Negative X
				rotor = Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(90.0f),
					Engine::Math::Vector3(0.0f, 1.0f, 0.0f));
				break;
			case 0:
				//Positive X
				rotor = Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(-90.0f),
					Engine::Math::Vector3(0.0f, 1.0f, 0.0f));
				break;
			}
						
			cubeMapCameraTransform.setOrientation(rotor);
			environmentCamera->setTransform(cubeMapCameraTransform.getPosition(), cubeMapCameraTransform.getOrientation());
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffer[i]);
			GLenum errorCode = glGetError();
			WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to bind framebuffer");
			glViewport(0, 0, textureWidth, textureHeight);
			errorCode = glGetError();
			WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to set ViewPort");
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			errorCode = glGetError();
			WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to set clear color");
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			errorCode = glGetError();
			WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to clear color and depth buffer");
			renderScene();
			/*break;*/
		}

		environmentCamera->activateCamera(false);
		environmentCamera->setTransform(environmentCamera->getTransform().getPosition(),Engine::Math::Quaternion::getIdentityQuartenion());
		previousCamera->activateCamera(true);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		GLenum errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to bind framebuffer");
		glViewport(0, 0, textureWidth, textureHeight);
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to set ViewPort");
		glClearColor(0.0, 0.0, 1.0, 1.0);
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to set clear color");
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to clear color and depth buffer");
		Texture::addTextureToList(Material::getMaterial(materialName.c_str())->getEffectName(),
			textureName.c_str(), 
			texture, dynamicTextureSamplerName.c_str(),
			Fragment, TextureType::TEXTURE_CUBE);
	}
	else
	{
		errormessage << "Unable to initialize the texture";
		MessageBox(nullptr, errormessage.str().c_str(), nullptr, MB_OK);
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}


void Engine::Graphics::ReflectingObject::renderScene()
{
	SharedPointer<Engine::Scene> currentScene =
		Engine::Scene::getRenderableScene();

	Engine::SharedPointer<Engine::Graphics::SkyBox> tempSkyBox =
		Engine::Graphics::SkyBox::getCurrentSkyBox();

	if (!tempSkyBox.isNull() && tempSkyBox->isSkyBoxAvailableIntialized())
	{
		tempSkyBox->draw(true);
	}

	for (uint8_t i = 0; i < currentScene->getMeshObjectList().size(); i++)
		currentScene->getMeshObjectList()[i]->draw(false);

	for (uint8_t i = 0; i < currentScene->getSpriteObjectList().size(); i++)
		currentScene->getSpriteObjectList()[i]->draw(false);

	if (Engine::Graphics::Line::containsDebugLine())
		Engine::Graphics::Line::drawLines(false);
}


bool Engine::Graphics::ReflectingObject::init()
{
	if (!cubeMapGenerated)
	{
		GLuint width = Engine::Windows::WindowingSystem::getWindowingSystem()->getWindowWidth();
		GLuint height = Engine::Windows::WindowingSystem::getWindowingSystem()->getWindowHeight();
		bool wereThereErrors = false;;
		//cretating textures
		{
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
			GLenum errorCode;
			errorCode = glGetError();
			if (errorCode == GL_NO_ERROR)
			{
				for (int i = 0; i < 6; i++)
				{
					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
						0, GL_RGBA, 2048, 2048, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, nullptr);
					errorCode = glGetError();
					WindowsUtil::Assert(glGetError() == GL_NO_ERROR, "Unable to create mutable texture");
				}
			}
			else
				wereThereErrors = true;
		}

		//Creating the render buffers
		{
			glGenRenderbuffers(6, renderBuffer);
			for (int i = 0; i < 6; i++)
			{
				glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer[i]);
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 2048, 2048);
				GLenum errorCode = glGetError();
				wereThereErrors |= errorCode == GL_NO_ERROR ? false : true;
				WindowsUtil::Assert(!wereThereErrors, "Unable to bind or create the buffer storage for the render buffer");
			}
		}

		//Creating Frame Buffers
		{
			glGenFramebuffers(6, frameBuffer);
			for (int i = 0; i < 6; i++)
			{
				glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffer[i]);
				glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER,
					GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, texture, 0);
				GLenum errorCode = glGetError();
				wereThereErrors |= errorCode == GL_NO_ERROR ? false : true;
				WindowsUtil::Assert(!wereThereErrors, "Unable to bind or create the buffer storage for the frame buffer");
			}
		}
		cubeMapGenerated = true;
		return !wereThereErrors;
	}
	return true;
}


void Engine::Graphics::ReflectingObject::draw(bool)
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
		
		

		std::string effectFile = Material::getMaterial(materialName.c_str())->getEffectName();
		SharedPointer<Effect> tempEffect = Effect::getEffect(effectFile);
		
		tempEffect->setShaders();
		Math::Transform gameObjectTransform = getTransform();
		

		SharedPointer<Graphics::Uniform> localToWorldUniform =
			Graphics::Uniform::getUniform(
				tempEffect->getTransformMatrixUniformName(
					Graphics::Vertex,
					Graphics::LocalToWorld), effectFile, Graphics::Vertex);

		SharedPointer<Graphics::Uniform> worldToView = Graphics::Uniform::getUniform(
			tempEffect->getTransformMatrixUniformName(
				Graphics::Vertex,
				Graphics::WorldToView), effectFile, Graphics::Vertex);

		SharedPointer<Graphics::Uniform> scaleMatrix = Graphics::Uniform::getUniform(
			tempEffect->getTransformMatrixUniformName(
				Graphics::Vertex,
				Graphics::ScaleMatrix), effectFile, Graphics::Vertex);

		SharedPointer<Graphics::Uniform> viewToScreen = Graphics::Uniform::getUniform(
			tempEffect->getTransformMatrixUniformName(
				Graphics::Vertex,
				Graphics::ViewToScreen), effectFile, Graphics::Vertex);

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

		tempColor.vectorValue.x = 1.0f;
		tempColor.vectorValue.y = 1.0f;
		tempColor.vectorValue.z = 1.0f;
		tempColor.vectorValue.w = 1.0f;

		SharedPointer<Engine::Graphics::Uniform> vertexColorUiform
			= Engine::Graphics::Uniform::getUniform("vertexColorModifier",
				effectFile, Graphics::Vertex);
		vertexColorUiform->setUniformValue(tempColor);
		Engine::Graphics::Material::getMaterial(materialName.c_str())->changeMaterialColor(1.0f, 1.0f, 1.0f);
		Engine::Graphics::Uniform::setAllUniformToShaderObjects(effectFile);
		UniformBlock::setAllUniformBlockForTheEffectInShader(effectFile);
		Engine::Graphics::Material::getMaterial(materialName.c_str())->setMaterialUniformParameters();
		Engine::Graphics::Texture::getTexture(textureName.c_str())->setTextureInShaderObject(0);
		Engine::Graphics::Mesh::getMesh(meshName)->drawMesh();
		
	}
	else
	{
		std::stringstream errormessage;
		errormessage << "Camera is not iniitalized\n";
		WindowsUtil::Print(errormessage.str().c_str());
		return;
	}
}



