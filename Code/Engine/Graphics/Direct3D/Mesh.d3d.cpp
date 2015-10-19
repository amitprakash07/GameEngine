#include "../Mesh.h"
#include "../Graphics.h"
#include <assert.h>
#include <stdint.h>
#include "../../Windows/WindowsFunctions.h"

namespace Engine
{
	namespace Graphics
	{
		HRESULT GetVertexProcessingUsage(DWORD& o_usage);
	}
}

bool Engine::Graphics::Mesh::drawMesh()
{
	std::stringstream errormessage;
	if (!createVertexBuffer())
	{
		errormessage << "Unable to Create VertexBuffer for the Mesh.";
		WindowsUtil::Print(errormessage.str());
		return false;
	}
	if (!createIndexBuffer())
	{
		errormessage << "Unable to create Index Buffer for the Mesh.";
		WindowsUtil::Print(errormessage.str());
		return false;
	}
	HRESULT result;
	// Bind a specific vertex buffer to the device as a data source
	
		// There can be multiple streams of data feeding the display adaptor at the same time
		const unsigned int streamIndex = 0;
		// It's possible to start streaming data in the middle of a vertex buffer
		const unsigned int bufferOffset = 0;
		// The "stride" defines how large a single vertex is in the stream of data
		const unsigned int bufferStride = sizeof(Engine::Graphics::vertex);
		result = Engine::Graphics::GraphicsSystem::getDevice()->SetStreamSource(streamIndex, s_vertexBuffer, bufferOffset, bufferStride);
		assert(SUCCEEDED(result));
	

	// Bind a specific index buffer to the device as a data source
	
		result = Engine::Graphics::GraphicsSystem::getDevice()->SetIndices(s_indexBuffer);
		assert(SUCCEEDED(result));
	

	// Render objects from the current streams
	
		// We are using triangles as the "primitive" type,
		// and we have defined the vertex buffer as a triangle list
		// (meaning that every triangle is defined by three vertices)
		const D3DPRIMITIVETYPE primitiveType = D3DPT_TRIANGLELIST;
		// It's possible to start rendering primitives in the middle of the stream
		const unsigned int indexOfFirstVertexToRender = 0;
		const unsigned int indexOfFirstIndexToUse = 0;
		// We are drawing a square
		const unsigned int vertexCountToRender = 3; // @Amit - Made three as each triangle needs three vertices from the vertex buffer EAE6320_TODO;	// How vertices from the vertex buffer will be used?
		const unsigned int primitiveCountToRender = triangleCount; // EAE6320_TODO;	// How many triangles will be drawn?

		result = Engine::Graphics::GraphicsSystem::getDevice()->DrawIndexedPrimitive(primitiveType,
			indexOfFirstVertexToRender, indexOfFirstVertexToRender, vertexCountToRender,
			indexOfFirstIndexToUse, primitiveCountToRender);
		
		return(SUCCEEDED(result));	
}

bool Engine::Graphics::Mesh::createVertexBuffer()
{
	DWORD usage = 0;
	// The type of vertex processing should match what was specified when the device interface was created with CreateDevice()
	const HRESULT vertexProcessingresult = GetVertexProcessingUsage(usage);
	if (FAILED(vertexProcessingresult))
	{
		return false;
	}
		
	// Our code will only ever write to the buffer
	usage |= D3DUSAGE_WRITEONLY;
	

	/******************************** Initialize the vertex format********************************************/
	/* These elements must match the VertexFormat::sVertex layout struct exactly.
	 They instruct Direct3D how to match the binary data in the vertex buffer
	 to the input elements in a vertex shader
	 (by using D3DDECLUSAGE enums here and semantics in the shader,
	 so that, for example, D3DDECLUSAGE_POSITION here matches with POSITION in shader code).
	 Note that OpenGL uses arbitrarily assignable number IDs to do the same thing.*/
	D3DVERTEXELEMENT9 vertexElements[] =
	{
			// Stream 0, POSITION( 2 floats == 8 bytes), Offset = 0
		{ 0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		// COLOR0, D3DCOLOR == 4 bytes, Offset = 8(from Position)
		{ 0, 8, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
		// The following marker signals the end of the vertex declaration
		D3DDECL_END()
	};

	HRESULT vertexDeclerationResult = Engine::Graphics::GraphicsSystem::getDevice()->CreateVertexDeclaration(vertexElements, &s_vertexDeclaration);

	if (SUCCEEDED(vertexDeclerationResult))
	{
		vertexDeclerationResult = Engine::Graphics::GraphicsSystem::getDevice()->SetVertexDeclaration(s_vertexDeclaration);
		if (FAILED(vertexDeclerationResult))
		{
			WindowsUtil::Print("Direct3D failed to set the vertex declaration");
			return false;
		}
	}
	else
	{
		WindowsUtil::Print("Direct3D failed to create a Direct3D9 vertex declaration");
		return false;
	}
	

	// Create a vertex buffer
	
	const unsigned int bufferSize = vertexCount * sizeof(vertex);

	// We will define our own vertex format
	const DWORD useSeparateVertexDeclaration = 0;

	// Place the vertex buffer into memory that Direct3D thinks is the most appropriate
	const D3DPOOL useDefaultPool = D3DPOOL_DEFAULT;
	HANDLE* const notUsed = nullptr;
	const HRESULT vertexBufferResult = Engine::Graphics::GraphicsSystem::getDevice()->CreateVertexBuffer(bufferSize, usage, useSeparateVertexDeclaration, useDefaultPool,
			&s_vertexBuffer, notUsed);

	if (FAILED(vertexBufferResult))
	{
		WindowsUtil::Print("Direct3D failed to create a vertex buffer");
		return false;
	}
	
	//Filling the vertex buffer
	// Before the vertex buffer can be changed it must be "locked"
	vertex* vertexData;
	const unsigned int lockEntireBuffer = 0;
	const DWORD useDefaultLockingBehavior = 0;
	const HRESULT result = s_vertexBuffer->Lock(lockEntireBuffer, lockEntireBuffer,
				reinterpret_cast<void**>(&vertexData), useDefaultLockingBehavior);
	if (FAILED(result))
	{
		WindowsUtil::Print("Direct3D failed to lock the vertex buffer");
		return false;
	}
	
	memcpy(vertexData, mVertex, sizeof(mVertex[0]) * vertexCount); //*****************Amit***************************

	// The buffer must be "unlocked" before it can be used
	const HRESULT vertexBufferunlockResult = s_vertexBuffer->Unlock();
	if (FAILED(vertexBufferunlockResult))
	{
		WindowsUtil::Print("Direct3D failed to unlock the vertex buffer");
		return false;
	}
		
	return true;

}

bool Engine::Graphics::Mesh::createIndexBuffer()
{
	// The usage tells Direct3D how this vertex buffer will be used
	DWORD usage = 0;
	
	// The type of vertex processing should match what was specified when the device interface was created with CreateDevice()
	const HRESULT vertexProcessingUsageResult = GetVertexProcessingUsage(usage);
	if (FAILED(vertexProcessingUsageResult))
	{
		return false;
	}
	// Our code will only ever write to the buffer
	usage |= D3DUSAGE_WRITEONLY;
	
	// Create an index buffer
	unsigned int bufferSize;
	
	bufferSize = triangleCount * 3 * sizeof(uint32_t);   

	// We'll use 32-bit indices in this class to keep things simple
	// (i.e. every index will be a 32 bit unsigned integer)
	const D3DFORMAT format = D3DFMT_INDEX32;

	// Place the index buffer into memory that Direct3D thinks is the most appropriate
	const D3DPOOL useDefaultPool = D3DPOOL_DEFAULT;
	HANDLE* notUsed = nullptr;
	const HRESULT indexBufferCreationResult = Engine::Graphics::GraphicsSystem::getDevice()->CreateIndexBuffer(bufferSize, usage, format, useDefaultPool,
				&s_indexBuffer, notUsed);
	if (FAILED(indexBufferCreationResult))
	{
		WindowsUtil::Print("Direct3D failed to create an index buffer");
		return false;
	}
		

	// Fill the index buffer with the triangles' connectivity data
	// Before the index buffer can be changed it must be "locked"
	uint32_t* indexData;
	const unsigned int lockEntireBuffer = 0;
	const DWORD useDefaultLockingBehavior = 0;
	const HRESULT result = s_indexBuffer->Lock(lockEntireBuffer, lockEntireBuffer,
					reinterpret_cast<void**>(&indexData), useDefaultLockingBehavior);

	if (FAILED(result))
	{
		WindowsUtil::Print("Direct3D failed to lock the index buffer");
		return false;
	}
	
	uint32_t * tempIndicesList = getIndices();
	memcpy(indexData, tempIndicesList, sizeof(uint32_t) * triangleCount* 3);
	
	// The buffer must be "unlocked" before it can be used
	const HRESULT unlockIndexBufferResult = s_indexBuffer->Unlock();
	if (FAILED(unlockIndexBufferResult))
	{
		WindowsUtil::Print("Direct3D failed to unlock the index buffer");
		return false;
	}
	
	return true;
}

HRESULT Engine::Graphics::GetVertexProcessingUsage(DWORD& o_usage)
{
	D3DDEVICE_CREATION_PARAMETERS deviceCreationParameters;
	const HRESULT result = Engine::Graphics::GraphicsSystem::getDevice()->GetCreationParameters(&deviceCreationParameters);
	if (SUCCEEDED(result))
	{
		DWORD vertexProcessingType = deviceCreationParameters.BehaviorFlags &
			(D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MIXED_VERTEXPROCESSING | D3DCREATE_SOFTWARE_VERTEXPROCESSING);
		o_usage = (vertexProcessingType != D3DCREATE_SOFTWARE_VERTEXPROCESSING) ? 0 : D3DUSAGE_SOFTWAREPROCESSING;
	}
	else
	{
		WindowsUtil::Print("Direct3D failed to get the device's creation parameters");
	}
	return result;
}

Engine::Graphics::Mesh::~Mesh()
{
	if (mVertex)
	{
		delete mVertex;
		mVertex = nullptr;
	}
	if (mIndices)
	{
		delete mIndices;
		mIndices = nullptr;
	}
	if (s_vertexBuffer)
		s_vertexBuffer->Release();

	if (s_indexBuffer)
		s_indexBuffer->Release();

	if (s_vertexDeclaration)
	{
		GraphicsSystem::getDevice()->SetVertexDeclaration(nullptr);
		s_vertexDeclaration->Release();
	}

	s_vertexBuffer = nullptr;
	s_indexBuffer = nullptr;
	s_vertexDeclaration = nullptr;

}

Engine::Graphics::Mesh::Mesh(std::string i_meshName, std::string i_fileName)
{
	s_vertexBuffer = nullptr;
	s_indexBuffer = nullptr;
	s_vertexDeclaration = nullptr;
	mVertex = nullptr;
	mIndices = nullptr;
	meshFileName = i_fileName;
	meshName = i_meshName;
	triangleCount = 0;
	vertexCount = 0;
	mWinding = Engine::Graphics::winding::LEFT;
}



