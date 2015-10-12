#pragma once

#include "../Mesh.h"
#include <assert.h>
#include <gl/GLU.h>
#include "../../Windows/WindowsFunctions.h"

bool Engine::Graphics::Mesh::drawMesh()
{

	// Bind a specific vertex buffer to the device as a data source
	glBindVertexArray(s_vertexArrayID);
	assert(glGetError() == GL_NO_ERROR);
	
	// Render objects from the current streams
	// We are using triangles as the "primitive" type,
	// and we have defined the vertex buffer as a triangle list
	// (meaning that every triangle is defined by three vertices)
	const GLenum mode = GL_TRIANGLES;
	// We'll use 32-bit indices in this class to keep things simple
	// (i.e. every index will be a 32 bit unsigned integer)
	const GLenum indexType = GL_UNSIGNED_INT;
	// It is possible to start rendering in the middle of an index buffer
	const GLvoid* const offset = 0;
	// We are drawing a square
	const GLsizei primitiveCountToRender = triangleCount;
	const GLsizei vertexCountToRender = primitiveCountToRender * 3;
	glDrawElements(mode, vertexCountToRender, indexType, offset);
	assert(glGetError() == GL_NO_ERROR);
	return (glGetError() == GL_NO_ERROR);
}
bool Engine::Graphics::Mesh::createVertexArray()
{
	bool wereThereErrors = false;
	GLuint vertexBufferId = 0;
	GLuint indexBufferId = 0;

	// Create a vertex array object and make it active
	{
		const GLsizei arrayCount = 1;
		glGenVertexArrays(arrayCount, &s_vertexArrayID);
		const GLenum errorCode = glGetError();
		if (errorCode == GL_NO_ERROR)
		{
			glBindVertexArray(s_vertexArrayID);
			const GLenum errorCode = glGetError();
			if (errorCode != GL_NO_ERROR)
			{
				wereThereErrors = true;
				std::stringstream errorMessage;
				errorMessage << "OpenGL failed to bind the vertex array: " <<
					reinterpret_cast<const char*>(gluErrorString(errorCode));
				WindowsUtil::Print( errorMessage.str() );
				goto OnExit;
			}
		}
		else
		{
			wereThereErrors = true;
			std::stringstream errorMessage;
			errorMessage << "OpenGL failed to get an unused vertex array ID: " <<
				reinterpret_cast<const char*>(gluErrorString(errorCode));
			WindowsUtil::Print( errorMessage.str() );
			goto OnExit;
		}
	}

	// Create a vertex buffer object and make it active
	{
		const GLsizei bufferCount = 1;
		glGenBuffers(bufferCount, &vertexBufferId);
		const GLenum errorCode = glGetError();
		if (errorCode == GL_NO_ERROR)
		{
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
			const GLenum errorCode = glGetError();
			if (errorCode != GL_NO_ERROR)
			{
				wereThereErrors = true;
				std::stringstream errorMessage;
				errorMessage << "OpenGL failed to bind the vertex buffer: " <<
					reinterpret_cast<const char*>(gluErrorString(errorCode));
				WindowsUtil::Print( errorMessage.str() );
				goto OnExit;
			}
		}
		else
		{
			wereThereErrors = true;
			std::stringstream errorMessage;
			errorMessage << "OpenGL failed to get an unused vertex buffer ID: " <<
				reinterpret_cast<const char*>(gluErrorString(errorCode));
			WindowsUtil::Print( errorMessage.str() );
			goto OnExit;
		}
	}


	// Assign the data to the buffer
	{
		vertex *vertexData = new vertex[vertexCount];
		// Fill in the data for the triangle
		{
			Engine::Graphics::vertex* tempVertex = getVertex();
			memcpy(vertexData, tempVertex, sizeof(tempVertex[0]) * vertexCount); 
		}
		glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(vertex), reinterpret_cast<GLvoid*>(vertexData),
			// Our code will only ever write to the buffer
			GL_STATIC_DRAW);
		delete vertexData;
		const GLenum errorCode = glGetError();
		if (errorCode != GL_NO_ERROR)
		{
			wereThereErrors = true;
			std::stringstream errorMessage;
			errorMessage << "OpenGL failed to allocate the vertex buffer: " <<
				reinterpret_cast<const char*>(gluErrorString(errorCode));
			WindowsUtil::Print( errorMessage.str() );
			goto OnExit;
		}
	}
	// Initialize the vertex format
	{
		const GLsizei stride = sizeof(vertex);
		GLvoid* offset = 0;

		// Position (0)
		// 2 floats == 8 bytes
		// Offset = 0
		{
			const GLuint vertexElementLocation = 0;
			const GLint elementCount = 2;
			const GLboolean notNormalized = GL_FALSE;	// The given floats should be used as-is
			glVertexAttribPointer(vertexElementLocation, elementCount, GL_FLOAT, notNormalized, stride, offset);
			const GLenum errorCode = glGetError();
			if (errorCode == GL_NO_ERROR)
			{
				glEnableVertexAttribArray(vertexElementLocation);
				const GLenum errorCode = glGetError();
				if (errorCode == GL_NO_ERROR)
				{
					offset = reinterpret_cast<GLvoid*>(reinterpret_cast<uint8_t*>(offset) + (elementCount * sizeof(float)));
				}
				else
				{
					wereThereErrors = true;
					std::stringstream errorMessage;
					errorMessage << "OpenGL failed to enable the POSITION vertex attribute: " <<
						reinterpret_cast<const char*>(gluErrorString(errorCode));
					WindowsUtil::Print( errorMessage.str() );
					goto OnExit;
				}
			}
			else
			{
				wereThereErrors = true;
				std::stringstream errorMessage;
				errorMessage << "OpenGL failed to set the POSITION vertex attribute: " <<
					reinterpret_cast<const char*>(gluErrorString(errorCode));
				WindowsUtil::Print( errorMessage.str() );
				goto OnExit;
			}
		}
		// Color (1)
		// 4 uint8_ts == 4 bytes
		// Offset = 8
		{
			const GLuint vertexElementLocation = 1;
			const GLint elementCount = 4;
			const GLboolean normalized = GL_TRUE;
			glVertexAttribPointer(vertexElementLocation, elementCount, GL_UNSIGNED_BYTE, normalized, stride, offset);
			const GLenum errorCode = glGetError();
			if (errorCode == GL_NO_ERROR)
			{
				glEnableVertexAttribArray(vertexElementLocation);
				const GLenum errorCode = glGetError();
				if (errorCode == GL_NO_ERROR)
				{
					offset = reinterpret_cast<GLvoid*>(reinterpret_cast<uint8_t*>(offset) + (elementCount * sizeof(uint8_t)));
				}
				else
				{
					wereThereErrors = true;
					std::stringstream errorMessage;
					errorMessage << "OpenGL failed to enable the COLOR0 vertex attribute: " <<
						reinterpret_cast<const char*>(gluErrorString(errorCode));
					WindowsUtil::Print( errorMessage.str() );
					goto OnExit;
				}
			}
			else
			{
				wereThereErrors = true;
				std::stringstream errorMessage;
				errorMessage << "OpenGL failed to set the COLOR0 vertex attribute: " <<
					reinterpret_cast<const char*>(gluErrorString(errorCode));
				WindowsUtil::Print( errorMessage.str() );
				goto OnExit;
			}
		}
	}

	// Create an index buffer object and make it active
	{
		const GLsizei bufferCount = 1;
		glGenBuffers(bufferCount, &indexBufferId);
		const GLenum errorCode = glGetError();
		if (errorCode == GL_NO_ERROR)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
			const GLenum errorCode = glGetError();
			if (errorCode != GL_NO_ERROR)
			{
				wereThereErrors = true;
				std::stringstream errorMessage;
				errorMessage << "OpenGL failed to bind the index buffer: " <<
					reinterpret_cast<const char*>(gluErrorString(errorCode));
				WindowsUtil::Print( errorMessage.str() );
				goto OnExit;
			}
		}
		else
		{
			wereThereErrors = true;
			std::stringstream errorMessage;
			errorMessage << "OpenGL failed to get an unused index buffer ID: " <<
				reinterpret_cast<const char*>(gluErrorString(errorCode));
			WindowsUtil::Print( errorMessage.str() );
			goto OnExit;
		}
	}
	// Allocate space and copy the triangle data into the index buffer
	{
		const unsigned int vertexCountPerTriangle = 3;
		uint32_t *indexData = new uint32_t[triangleCount * vertexCountPerTriangle];
		// Fill in the data for the triangle
		{
			
			uint32_t * tempIndicesList = Engine::Graphics::Mesh::getIndices();
			memcpy(indexData, tempIndicesList, sizeof(uint32_t) * triangleCount* vertexCountPerTriangle);
		}

		const GLsizeiptr bufferSize = triangleCount * vertexCountPerTriangle * sizeof(uint32_t);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, reinterpret_cast<const GLvoid*>(indexData),
			// Our code will only ever write to the buffer
			GL_STATIC_DRAW);
		delete indexData;
		const GLenum errorCode = glGetError();
		if (errorCode != GL_NO_ERROR)
		{
			wereThereErrors = true;
			std::stringstream errorMessage;
			errorMessage << "OpenGL failed to allocate the index buffer: " <<
				reinterpret_cast<const char*>(gluErrorString(errorCode));
			WindowsUtil::Print( errorMessage.str() );
			goto OnExit;
		}

	}

OnExit:

	// Delete the buffer object
	// (the vertex array will hold a reference to it)
	if (s_vertexArrayID != 0)
	{
		// Unbind the vertex array
		// (this must be done before deleting the vertex buffer)
		glBindVertexArray(0);
		const GLenum errorCode = glGetError();
		if (errorCode == GL_NO_ERROR)
		{
			if (vertexBufferId != 0)
			{
				// NOTE: If you delete the vertex buffer object here, as I recommend,
				// then gDEBugger won't know about it and you won't be able to examine the data.
				// If you find yourself in a situation where you want to see the buffer object data in gDEBugger
				// comment out this block of code temporarily
				// (doing this will cause a memory leak so make sure to restore the deletion code after you're done debugging).
				const GLsizei bufferCount = 1;
				glDeleteBuffers(bufferCount, &vertexBufferId);
				const GLenum errorCode = glGetError();
				if (errorCode != GL_NO_ERROR)
				{
					wereThereErrors = true;
					std::stringstream errorMessage;
					errorMessage << "OpenGL failed to delete the vertex buffer: " <<
						reinterpret_cast<const char*>(gluErrorString(errorCode));
					WindowsUtil::Print( errorMessage.str() );
				}
				vertexBufferId = 0;
			}
			if (indexBufferId != 0)
			{
				// NOTE: See the same comment above about deleting the vertex buffer object here and gDEBugger
				// holds true for the index buffer
				const GLsizei bufferCount = 1;
				glDeleteBuffers(bufferCount, &indexBufferId);
				const GLenum errorCode = glGetError();
				if (errorCode != GL_NO_ERROR)
				{
					wereThereErrors = true;
					std::stringstream errorMessage;
					errorMessage << "\nOpenGL failed to delete the index buffer: " <<
						reinterpret_cast<const char*>(gluErrorString(errorCode));
					WindowsUtil::Print( errorMessage.str() );
				}
				indexBufferId = 0;
			}
		}
		else
		{
			wereThereErrors = true;
			std::stringstream errorMessage;
			errorMessage << "OpenGL failed to unbind the vertex array: " <<
				reinterpret_cast<const char*>(gluErrorString(errorCode));
			WindowsUtil::Print( errorMessage.str() );
		}
	}

	return !wereThereErrors;
}

Engine::Graphics::Mesh::~Mesh()
{
	if (mVertex)
		delete mVertex;
	if (mIndices)
		delete mIndices;

	mVertex = nullptr;
	mIndices = nullptr;
}

Engine::Graphics::Mesh::Mesh(std::string i_meshName, std::string i_fileName)
{
	mVertex = nullptr;
	mIndices = nullptr;
	meshFileName = i_fileName;
	meshName = i_meshName;
	mWinding = Engine::Graphics::winding::RIGHT;
	triangleCount = 0;
	vertexCount = 0;
}
