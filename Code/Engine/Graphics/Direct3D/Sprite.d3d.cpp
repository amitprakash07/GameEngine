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
	int windowWidth = EngineCore::getWindowingSystem()->getWindowWidth() / 2;
	int windowHeight = EngineCore::getWindowingSystem()->getWindowHeight() / 2;

	switch (i_coordinate)
	{
	case VIEWPORT_COORDINATE:
		left = Math::scaleAndBias(left, -windowWidth, windowWidth, -1, 1);
		right = Math::scaleAndBias(right, -windowWidth, windowWidth, -1, 1);
		top = Math::scaleAndBias(top, -windowHeight, windowHeight, -1, 1);
		bottom = Math::scaleAndBias(bottom, static_cast<float>(-windowHeight),
			static_cast<float>(windowHeight), -1.0f, 1.0f);
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
	s_vertexBuffer = nullptr;
	s_vertexDeclaration = nullptr;
}

bool Engine::Graphics::Sprite::createBuffers()
{
	return (createVertexBuffer());
}


bool Engine::Graphics::Sprite::createVertexBuffer()
{
	DWORD usage = 0;
	/*
	The type of vertex processing should match what was
	specified when the device interface was created with CreateDevice()
	*/
	const HRESULT vertexProcessingresult = GetVertexProcessingUsage(usage);
	if (FAILED(vertexProcessingresult))
		return false;

	// This will make sure we can change the position of the buffer
	usage |= D3DUSAGE_WRITEONLY || D3DUSAGE_DYNAMIC;


	/*
	Vertex Format - Similar to Vertex Attribute Pointer of OpenGL
	*/
	D3DVERTEXELEMENT9 vertexElements[] =
	{
		// Stream 0, POSITION( 3 floats == 12 bytes), Offset = 0
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 }, //Position
																					   // This will marker signals the end of the vertex declaration
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
	const unsigned int bufferSize = 4 * sizeof(float); //We need only four vertices for sprite

													   // We will define our own vertex format
	const DWORD useSeparateVertexDeclaration = 0;

	// Place the vertex buffer into memory that Direct3D thinks is the most appropriate
	const D3DPOOL useDefaultPool = D3DPOOL_DEFAULT;
	HANDLE* const notUsed = nullptr;

	/*
	HRESULT CreateVertexBuffer(
	[in]          UINT                   Length,
	[in]          DWORD                  Usage,
	[in]          DWORD                  FVF,
	[in]          D3DPOOL                Pool,
	[out, retval] IDirect3DVertexBuffer9 **ppVertexBuffer,
	[in]          HANDLE                 *pSharedHandle
	);
	*/
	const HRESULT vertexBufferResult = Engine::Graphics::GraphicsSystem::getDevice()->CreateVertexBuffer(bufferSize,
		usage, useSeparateVertexDeclaration, useDefaultPool,
		&s_vertexBuffer, notUsed);

	if (FAILED(vertexBufferResult))
	{
		WindowsUtil::Print("Direct3D failed to create a vertex buffer");
		return false;
	}

	return true && writeToBuffer();
}


void Engine::Graphics::Sprite::draw(bool)
{
	HRESULT result;

	// There can be multiple streams of data feeding the display adaptor at the same time
	const unsigned int streamIndex = 0;
	// It's possible to start streaming data in the middle of a vertex buffer
	const unsigned int bufferOffset = 0;
	// The "stride" defines how large a single vertex is in the stream of data
	const unsigned int bufferStride = sizeof(float) * 3;
	result = Engine::Graphics::GraphicsSystem::getDevice()->SetStreamSource(streamIndex, s_vertexBuffer, bufferOffset, bufferStride);
	assert(SUCCEEDED(result));

	/*
	HRESULT DrawPrimitive(
	[in] D3DPRIMITIVETYPE PrimitiveType,
	[in] UINT             StartVertex,
	[in] UINT             PrimitiveCount
	);
	*/
	result = Engine::Graphics::GraphicsSystem::getDevice()->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		2);

	WindowsUtil::Assert(SUCCEEDED(result));
}

bool Engine::Graphics::Sprite::writeToBuffer() const
{
	float* vertexData;
	const unsigned int lockEntireBuffer = 0;
	const DWORD useDefaultLockingBehavior = 0;
	// Before the vertex buffer can be changed it must be "locked"
	const HRESULT result = s_vertexBuffer->Lock(lockEntireBuffer, lockEntireBuffer,
		reinterpret_cast<void**>(&vertexData), useDefaultLockingBehavior);
	if (FAILED(result))
	{
		WindowsUtil::Print("Direct3D failed to lock the vertex buffer");
		return false;
	}

	float data[] = {
		rectLeft,rectBottom,1.0f,
		rectLeft,rectTop, 1.0f,
		rectRight, rectBottom, 1.0f,
		rectRight,rectTop,1.0f
	};

	memcpy(vertexData, data, sizeof(float) * 16);
	// unlockeing the buffer for use
	const HRESULT vertexBufferunlockResult = s_vertexBuffer->Unlock();
	if (FAILED(vertexBufferunlockResult))
	{
		WindowsUtil::Print("Direct3D failed to unlock the vertex buffer");
		return false;
	}

	return true;
}

Engine::Graphics::Sprite::~Sprite()
{
	if (s_vertexBuffer)
		s_vertexBuffer->Release();
	if (s_vertexDeclaration)
	{
		GraphicsSystem::getDevice()->SetVertexDeclaration(nullptr);
		s_vertexDeclaration->Release();
	}

	s_vertexBuffer = nullptr;
	s_vertexDeclaration = nullptr;
}







