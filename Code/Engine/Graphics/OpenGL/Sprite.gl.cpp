#include "../Sprite.h"
#include "../../Core/Maths/Functions.h"
#include "../../Windows/WindowsFunctions.h"
#include "../../Core/EngineCore/EngineCore.h"
#include "../Graphics.h"

Engine::Graphics::Sprite::Sprite(std::string iSpriteName,
	std::string iMaterialName,
	float left, 
	float right, 
	float top, 
	float bottom, 
	Coordinate i_coordinate)
{

	//Might need to change as OpenGL screen coordinate 
	//system is different than DirectX
	int windowWidth = EngineCore::getWindowingSystem()->getWindowWidth() / 2;
	int windowHeight = EngineCore::getWindowingSystem()->getWindowHeight() / 2;

	switch (i_coordinate)
	{
	case VIEWPORT_COORDINATE:
		left = Math::scaleAndBias(left, 0, windowWidth*2, -1, 1);
		right = Math::scaleAndBias(right, 0, windowWidth * 2, -1, 1);
		top = Math::scaleAndBias(top, 0, windowHeight * 2, -1, 1);
		bottom = Math::scaleAndBias(bottom, 0, windowHeight * 2, -1.0, 1.0);
		break;
	case TEXTURE_COORDINATE:
		left = Math::scaleAndBias(left, 0, 1, -1, 1);
		right = Math::scaleAndBias(right, 0, 1, -1, 1);
		top = Math::scaleAndBias(top, 0, 1, -1, 1);
		bottom = Math::scaleAndBias(bottom, 0, 1, -1, 1);
		break;
	case SCREEN_COORDINATE:
		break;
	}
	rectLeft = left;
	rectRight = right;
	rectTop = top;
	rectBottom = bottom;
	mSpriteName = iSpriteName;
	mMaterial = iMaterialName;
	s_vertexArrayID = 0;
	vertexBufferId = 0;
	indexBufferId = 0;
	isDebug = false;
	vertexAttribute = new vertexTexture[4];
	multiple = false;
	rows = columns = totalCells = cellToRender = 0;
}

void Engine::Graphics::Sprite::drawSprite()
{
	if (writeToBuffer())
	{
		GLenum errorCode;
		glBindVertexArray(s_vertexArrayID);
		errorCode = glGetError();
		glDrawElements(GL_TRIANGLES, 6/*Only 6 vertices is required for the triangle*/,
			GL_UNSIGNED_INT, 0);
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unbale to draw the quad");
	}
}


bool Engine::Graphics::Sprite::createBuffers()
{
	return (createVertexArray());
}

bool Engine::Graphics::Sprite::createVertexArray()
{
	GLenum errorCode;
	glGenVertexArrays(1, &s_vertexArrayID);
	errorCode = glGetError();
	glBindVertexArray(s_vertexArrayID);	
	errorCode = glGetError();
	if(WindowsUtil::Assert(errorCode==GL_NO_ERROR,
		"Unable to create or Bind Vertex Array"))
	{
		glGenBuffers(1, &vertexBufferId);
		errorCode = glGetError();
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
		if(WindowsUtil::Assert((errorCode = glGetError())==GL_NO_ERROR,
			"Unable to create or bind the vertex buffer"))
		{
			glGenBuffers(1, &indexBufferId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
			if(WindowsUtil::Assert((errorCode = glGetError())== GL_NO_ERROR,
				"Unable to bind or create index buffer"))
			{

				return true;
			}
		}
	}
	return false;
}




bool Engine::Graphics::Sprite::writeToBuffer()
{
	glBindVertexArray(s_vertexArrayID);
	GLenum errorCode;
	GLvoid * offset = 0;
	GLsizei stride = sizeof(vertexTexture);
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
	if(WindowsUtil::Assert(errorCode == GL_NO_ERROR, 
		"Unable to create vertex specification or enabling it went wrong"))
	{
		offset = 
			reinterpret_cast<void*>((reinterpret_cast<uint8_t*>(offset)) + sizeof(Math::Vector3));
		glVertexAttribPointer(
			1 /*Texture Coordinate*/,
			2,
			GL_FLOAT,
			GL_FALSE,
			stride,
			offset
			);

		glEnableVertexAttribArray(1);
		vertexTexture * data = getTextureAndVerticesData();

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexTexture) * 4 , data, GL_DYNAMIC_DRAW);
		if (WindowsUtil::Assert((errorCode = glGetError()) == GL_NO_ERROR,
			"Unable to store data to the vertex buffer"))
		{
			GLint indexData[] = {
				0,1,2,
				0,2,3
			};
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLint), indexData, GL_DYNAMIC_DRAW);
			if(WindowsUtil::Assert((errorCode = glGetError())==GL_NO_ERROR,
				"Unable to bind or pass data to index buffer"))
			{
				return true;
			}
		}
	}	
	return false;
}


Engine::Graphics::Sprite::~Sprite()
{
	if (vertexAttribute)
		delete vertexAttribute;
}



