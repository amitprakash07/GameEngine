#include "../SkyBox.h"
#include "../../Windows/WindowsFunctions.h"
#include "../../Graphics/Effect.h"
#include "../../Graphics/Material.h"
#include "../../Core/EngineCore/Objects/Camera.h"


namespace Engine
{
	class Scene :public RTTI
	{
	public:
		static Engine::SharedPointer<Scene> getRenderableScene();
		SharedPointer<Camera> getActiveCamera() const;		
	};
}


Engine::Graphics::SkyBox::SkyBox(std::string material_Name)
{
	mMaterialName = material_Name;
	s_vertexArrayID = -1;
	vertexBufferId = -1;
	indexBufferId = -1;
	isSkyBoxAvailable = false;
}


bool Engine::Graphics::SkyBox::createBuffer()
{
	bool ableToCreateVertexArray = createVertexArray();
	WindowsUtil::Assert(ableToCreateVertexArray, "Unabel to Create VertexArray for the SkyBox");
	return ableToCreateVertexArray;
}


bool Engine::Graphics::SkyBox::createVertexArray()
{
	glGenVertexArrays(1, &s_vertexArrayID);
	bool wereThereErrors = false;
	GLenum errorCode = glGetError();
	wereThereErrors = errorCode == GL_NO_ERROR ? false : true;
	WindowsUtil::Assert(!wereThereErrors, "Unable to Create VertexArray for the SkyBox");
	
	//Very Important 
	glBindVertexArray(s_vertexArrayID);
	

	glGenBuffers(1, &vertexBufferId);
	errorCode = glGetError();
	wereThereErrors |= errorCode == GL_NO_ERROR ? false : true;
	WindowsUtil::Assert(!wereThereErrors, "Unable to Create Vertex Buffer for the SkyBox");

	if(!wereThereErrors)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
		errorCode = glGetError();
		wereThereErrors |= errorCode == GL_NO_ERROR ? false : true;
		WindowsUtil::Assert(!wereThereErrors, "Unable to Bind Vertex Buffer for the SkyBox");
	}


	/*
	Vertex Struct for the Skybox needs 
	three floats for the vertex and
	same can be considered as the texture Coordinate
	*/

	GLfloat vertexDataForSkyBox[] =
	{
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexDataForSkyBox),
		vertexDataForSkyBox, GL_STATIC_DRAW);

	errorCode = glGetError();
	wereThereErrors |= errorCode == GL_NO_ERROR ? false : true;
	WindowsUtil::Assert(!wereThereErrors, "Unable to bind data to the Vertex Buffer for the SkyBox");

	//Declaring Vertex Structure
	glVertexAttribPointer(0, /* Only one location is required for the vertex*/
		3,  /*Only three floats for the vertex*/
		GL_FLOAT, /*Only Floats,*/
		GL_FALSE, /*No Normalization required*/
		12, /*Only 12 bytes required for three floats*/
		0 /*Starting location of this element in the stride*/);

	errorCode = glGetError();
	wereThereErrors |= errorCode == GL_NO_ERROR ? false : true;
	WindowsUtil::Assert(!wereThereErrors, "Unable to declare the vertex declaration for the SkyBox");

	glEnableVertexAttribArray(0);

	
	/*Generating the index buffer*/
	glGenBuffers(1, &indexBufferId);
	errorCode = glGetError();
	wereThereErrors |= errorCode == GL_NO_ERROR ? false : true;
	WindowsUtil::Assert(!wereThereErrors, "Unable to create Index Buffer for the SkyBox");
	if(!wereThereErrors)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
		errorCode = glGetError();
		wereThereErrors |= errorCode == GL_NO_ERROR ? false : true;
		WindowsUtil::Assert(!wereThereErrors, "Unable to bind the index buffer for the SkyBox");
	}

	/*Allocating the index Buffer in the left winding order for proper face culling*/
	//GLuint indexDataForTheSkyBox[] = {
	//	0,3,2,  0,2,1, //Front
	//	4,7,6,  4,6,5, //Back
	//	0,3,7,  0,7,6, //Left
	//	1,2,6,  1,6,5, //Right
	//	3,7,6,  3,6,2, //Top
	//	0,4,5,  0,5,1  //Bottom
	//};

	GLuint indexDataForTheSkyBox[] = {
		0,2,3,  0,1,2, //Front
		4,6,7,  4,5,6, //Back
		0,7,3,  0,4,7, //Left
		1,6,2,  1,5,6, //Right
		3,6,7,  3,2,6, //Top
		0,5,4,  0,1,5  //Bottom
	};

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexDataForTheSkyBox),
		indexDataForTheSkyBox, GL_STATIC_DRAW);

	wereThereErrors |= errorCode == GL_NO_ERROR ? false : true;
	WindowsUtil::Assert(!wereThereErrors, "Unable to bind the index data of the SkyBox");
	return !wereThereErrors;
}


void Engine::Graphics::SkyBox::draw(bool)
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

			SharedPointer<Graphics::Uniform> worldToView = Graphics::Uniform::getUniform(
				tempEffect->getTransformMatrixUniformName(
					Graphics::Vertex,
					Graphics::WorldToView), tempMaterial->getEffectName(), Graphics::Vertex);

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

			Engine::Graphics::Uniform::setAllUniformToShaderObjects(tempMaterial->getEffectName());
			tempMaterial->setMaterialUniformParameters();
			tempMaterial->setTextureUniform();
			glBindVertexArray(s_vertexArrayID);
			WindowsUtil::Assert(glGetError() == GL_NO_ERROR, "Unable to bind the vertex Array Object");

			const GLenum mode = GL_TRIANGLES;
			const GLenum indexType = GL_UNSIGNED_INT;
			const GLvoid* const offset = 0;
			glDrawElements(mode, 12 * 3, indexType, offset);
			WindowsUtil::Assert(glGetError() == GL_NO_ERROR, "Unable to Draw ths SkyBox");
			glClear(GL_DEPTH_BUFFER_BIT);
		}
	}	
}



