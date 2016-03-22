#include "../Plane.h"
#include "../../Windows/WindowsFunctions.h"
#include "../../Core/EngineCore/Objects/Camera.h"
#include "../Uniform.h"
#include "../Effect.h"
#include "../Material.h"


namespace Engine
{
	class Scene :public RTTI
	{
	public:
		static Engine::SharedPointer<Scene> getRenderableScene();
		SharedPointer<Camera> getActiveCamera() const;
	};
}


Engine::Graphics::Plane::Plane(std::string material_name)
{
	s_vertexArrayID = 0;
	vertexBufferId = 0;
	indexBufferId = 0;
	debugObject = false;
	scaleFactor = Math::Vector3(1.0f, 1.0f, 1.0f);
	mObjectController = nullptr;
	mTransform = Math::Transform();
	mMaterialName = material_name;
	vertexattribute = nullptr;
}


bool Engine::Graphics::Plane::createBuffer()
{
	return (createVertexArray() && writeToBuffer());
}


bool Engine::Graphics::Plane::createVertexArray()
{
	GLenum errorCode;
	glGenVertexArrays(1, &s_vertexArrayID);
	errorCode = glGetError();
	glBindVertexArray(s_vertexArrayID);
	errorCode = glGetError();
	if (WindowsUtil::Assert(errorCode == GL_NO_ERROR,
		"Unable to create or Bind Vertex Array"))
	{
		glGenBuffers(1, &vertexBufferId);
		errorCode = glGetError();
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
		if (WindowsUtil::Assert((errorCode = glGetError()) == GL_NO_ERROR,
			"Unable to create or bind the vertex buffer"))
		{
			glGenBuffers(1, &indexBufferId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
			if (WindowsUtil::Assert((errorCode = glGetError()) == GL_NO_ERROR,
				"Unable to bind or create index buffer"))
			{
				return true;
			}
		}
	}
	return false;
}


void Engine::Graphics::Plane::draw(bool drawDebugObject)
{
	Engine::SharedPointer<Material> tempMaterial =
		Engine::Graphics::Material::getMaterial(mMaterialName.c_str());
	WindowsUtil::Assert(!tempMaterial.isNull(), "Material for the skybox is not available");

	Engine::SharedPointer<Engine::Graphics::Effect> tempEffect =
		Engine::Graphics::Effect::getEffect(tempMaterial->getEffectName());

	bool isEffectFound = !tempEffect.isNull();

	WindowsUtil::Assert(isEffectFound, "No Effect Found for the SkyBox");

	if (isEffectFound)
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

			tempEffect->setShaders();

			SharedPointer<Graphics::Uniform> localToWorld = Graphics::Uniform::getUniform(
				tempEffect->getTransformMatrixUniformName(
					Graphics::Vertex,
					Graphics::LocalToWorld), tempMaterial->getEffectName(), Graphics::Vertex);

			SharedPointer<Graphics::Uniform> worldToView = Graphics::Uniform::getUniform(
				tempEffect->getTransformMatrixUniformName(
					Graphics::Vertex,
					Graphics::WorldToView), tempMaterial->getEffectName(), Graphics::Vertex);

			SharedPointer<Graphics::Uniform> viewToScreen = Graphics::Uniform::getUniform(
				tempEffect->getTransformMatrixUniformName(
					Graphics::Vertex,
					Graphics::ViewToScreen), tempMaterial->getEffectName(), Graphics::Vertex);

			SharedPointer<Graphics::Uniform> scaleMatrix = Graphics::Uniform::getUniform(
				tempEffect->getTransformMatrixUniformName(
					Graphics::Vertex,
					Graphics::ScaleMatrix), tempMaterial->getEffectName(), Graphics::Vertex);

			SharedPointer<Graphics::Uniform> normalMatrix = Graphics::Uniform::getUniform(
				tempEffect->getTransformMatrixUniformName(
					Graphics::Vertex,
					Graphics::NormalMatrix), tempMaterial->getEffectName(), Graphics::Vertex);

			if (!localToWorld.isNull())
			{
				Graphics::UniformValues localToWorlValues;
				localToWorlValues.matrixValue.Type = Graphics::LocalToWorld;
				localToWorlValues.matrixValue.matrix = Engine::Math::Matrix4x4(
					mTransform.getOrientation(),mTransform.getPosition());
				localToWorld->setUniformValue(localToWorlValues);
			}

			if (!worldToView.isNull())
			{
				Graphics::UniformValues worldToViewValues;
				worldToViewValues.matrixValue.Type = Graphics::WorldToView;				
				worldToViewValues.matrixValue.matrix = Engine::Math::Matrix4x4::CreateWorldToViewTransform(
					cameraTransform.getOrientation(), cameraTransform.getPosition());
				worldToView->setUniformValue(worldToViewValues);
			}

			if (!viewToScreen.isNull())
			{
				Graphics::UniformValues viewToScreenValues;
				viewToScreenValues.matrixValue.Type = Graphics::ViewToScreen;
				viewToScreenValues.matrixValue.matrix = Engine::Math::Matrix4x4::CreateViewToScreenTransform(
					fieldOfView, aspectRatio,
					nearPlane, farPlane);
				viewToScreen->setUniformValue(viewToScreenValues);
			}

			if(!scaleMatrix.isNull())
			{				
				Graphics::UniformValues scaleMatrixValues;
				scaleMatrixValues.matrixValue.Type = Graphics::ScaleMatrix;
				scaleMatrixValues.matrixValue.matrix = Engine::Math::Matrix4x4::CreateScaleMatrix(
					scaleFactor);
				scaleMatrix->setUniformValue(scaleMatrixValues);
			}

			if(!normalMatrix.isNull())
			{
				Graphics::UniformValues normalMatrixValues;
				normalMatrixValues.matrixValue.Type = Graphics::NormalMatrix;
				normalMatrixValues.matrixValue.matrix = Engine::Math::Matrix4x4::CreateNormalMatrix(
					Math::Matrix4x4(mTransform.getOrientation(), mTransform.getPosition()));
				normalMatrix->setUniformValue(normalMatrixValues);
			}

			Engine::Graphics::Uniform::setAllUniformToShaderObjects(tempMaterial->getEffectName());
			tempMaterial->setMaterialUniformParameters();
			tempMaterial->setTextureUniform();
			glBindVertexArray(s_vertexArrayID);
			WindowsUtil::Assert(glGetError() == GL_NO_ERROR, "Unable to bind the vertex Array Object");

			const GLenum mode = GL_TRIANGLES;
			const GLenum indexType = GL_UNSIGNED_INT;
			const GLvoid* const offset = 0;
			glDrawElements(mode, 6, indexType, offset);
			WindowsUtil::Assert(glGetError() == GL_NO_ERROR, "Unable to Draw the plane");		
		}
	}
}

bool Engine::Graphics::Plane::writeToBuffer()
{
	glBindVertexArray(s_vertexArrayID);
	GLenum errorCode;
	GLvoid * offset = 0;
	GLsizei stride = sizeof(VertexTextureNormal);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	errorCode = glGetError();
	glVertexAttribPointer(
		0,/*Position*/
		3,/*3 floats are required*/
		GL_FLOAT,
		GL_FALSE,
		stride,/*only position and texture coordinates need to be sent 20 bytes*/
		offset
		);
	errorCode = glGetError();
	glEnableVertexAttribArray(0);
	errorCode = glGetError();
	if (WindowsUtil::Assert(errorCode == GL_NO_ERROR,
		"Unable to create vertex specification or enabling it went wrong"))
	{
		offset =
			reinterpret_cast<void*>((reinterpret_cast<uint8_t*>(offset)) + sizeof(Math::Vector3));
		glVertexAttribPointer(
			1,/*Normal*/
			3,/*3 floats are required*/
			GL_FLOAT,
			GL_FALSE,
			stride,/*position, normal and texture coordinates need to be sent */
			offset
			);

		glEnableVertexAttribArray(1);
		offset =
			reinterpret_cast<void*>((reinterpret_cast<uint8_t*>(offset)) + sizeof(Math::Vector3));
		glVertexAttribPointer(
			2 /*Texture Coordinate*/,
			2,
			GL_FLOAT,
			GL_FALSE,
			stride,
			offset
			);

		glEnableVertexAttribArray(2);
		VertexTextureNormal * data = getVertexAttributeData();

		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR,
			"Unable to create vertex specification or enabling it went wrong");

		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexTextureNormal) * 4, data, GL_STATIC_DRAW);
		if (WindowsUtil::Assert((errorCode = glGetError()) == GL_NO_ERROR,
			"Unable to store data to the vertex buffer"))
		{
			GLint indexData[] = {
				0,1,2,
				0,2,3
			};
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLint), indexData, GL_STATIC_DRAW);
			if (WindowsUtil::Assert((errorCode = glGetError()) == GL_NO_ERROR,
				"Unable to bind or pass data to index buffer"))
			{
				return true;
			}
		}
	}
	return false;
}




