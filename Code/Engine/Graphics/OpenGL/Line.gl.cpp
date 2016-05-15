#include "../Line.h"
#include "../../Windows/WindowsFunctions.h"
#include "../Material.h"

GLuint Engine::Graphics::Line::s_vertexArrayID;
GLuint Engine::Graphics::Line::vertexBufferId;


void Engine::Graphics::Line::drawLines(bool drawDebugLines)
{
	GLenum errorCode;
	glLineWidth(2.0);
	if(writeToBuffer() && Engine::Graphics::Effect::getEffect(
		Engine::Graphics::Material::getMaterial(
			materialName.c_str())->getEffectName())->setShaders()
		&& setUniforms())
	{
		glBindVertexArray(s_vertexArrayID);
		if (WindowsUtil::Assert((errorCode = glGetError()) == GL_NO_ERROR, "Unable to create the vertex array"))
		{
			glDrawArrays(GL_LINES, 0, 2 * mLineList.size());
			WindowsUtil::Assert((errorCode = glGetError()) == GL_NO_ERROR, "Unable to draw the line");
		}
	}

	glLineWidth(1.0);	
}

bool Engine::Graphics::Line::createBuffer()
{
	if (!bufferInitialized)
	{
		GLenum errorCode;
		glGenVertexArrays(1, &s_vertexArrayID);
		if (WindowsUtil::Assert(glGetError() == GL_NO_ERROR, "Unable to create the vertex array"))
		{
			glBindVertexArray(s_vertexArrayID);
			if (WindowsUtil::Assert((errorCode = glGetError()) == GL_NO_ERROR, "Unable to bind the vertex array"))
			{
				glGenBuffers(1, &vertexBufferId);
				if (WindowsUtil::Assert((errorCode = glGetError()) == GL_NO_ERROR, "Unable to create the vertex buffer"))
				{
					glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
					if (WindowsUtil::Assert((errorCode = glGetError()) == GL_NO_ERROR, "Unable to bind the vertex buffer"))
					{
						bufferInitialized = true;
						return true;
					}
				}
			}

		}
		return false;
	}
	return true;
}

bool Engine::Graphics::Line::writeToBuffer()
{
	GLenum errorCode;
	GLvoid * offset = 0;
	glBindVertexArray(s_vertexArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glVertexAttribPointer(0 /*Vertex Location*/,
		3,
		GL_FLOAT,
		GL_FALSE,
		28/*3 Floatrs for position and 4 floats for color*/,
		offset);
	glEnableVertexAttribArray(0);
	offset = reinterpret_cast<uint8_t*>(offset) + sizeof(float) * 3;
	glVertexAttribPointer(1 /**/,
		4,
		GL_FLOAT,
		GL_FALSE,
		28,
		offset);
	glEnableVertexAttribArray(1);

	if (WindowsUtil::Assert((errorCode = glGetError()) == GL_NO_ERROR, "Unable to declare the vertex format"))
	{
		float *data = new float[sizeof(float) * 14 * mLineList.size()];
		for (int i = 0; i < mLineList.size(); i++)
		{
			//StartPoint
			data[14*i + 0] = mLineList[i]->mLineStruct.startPoint.x;
			data[14*i + 1] = mLineList[i]->mLineStruct.startPoint.y;
			data[14*i + 2] = mLineList[i]->mLineStruct.startPoint.z;
			data[14 * i + 3] = mLineList[i]->mLineStruct.color.r;
			data[14 * i + 4] = mLineList[i]->mLineStruct.color.g;
			data[14 * i + 5] = mLineList[i]->mLineStruct.color.b;
			data[14 * i + 6] = mLineList[i]->mLineStruct.color.a;

			//EndPoint
			data[14 * i + 7] = mLineList[i]->mLineStruct.endPoint.x;
			data[14 * i + 8] = mLineList[i]->mLineStruct.endPoint.y;
			data[14 * i + 9] = mLineList[i]->mLineStruct.endPoint.z;
			data[14 * i + 10] = mLineList[i]->mLineStruct.color.r;
			data[14 * i + 11] = mLineList[i]->mLineStruct.color.g;
			data[14 * i + 12] = mLineList[i]->mLineStruct.color.b;
			data[14 * i + 13] = mLineList[i]->mLineStruct.color.a;
		}

		glBufferData(GL_ARRAY_BUFFER, 14 * sizeof(float) * mLineList.size(), data, GL_STATIC_DRAW);
		if (WindowsUtil::Assert(glGetError() == GL_NO_ERROR, "Unable to declare the vertex format"))
		{
			return true;
		}
	}
	return false;
}


