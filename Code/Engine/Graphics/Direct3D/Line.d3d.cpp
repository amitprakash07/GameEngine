#include "../Line.h"
#include "../../Core/Maths/Functions.h"
#include "../../Windows/WindowsFunctions.h"
#include "../../Core/EngineCore/EngineCore.h"
#include "../Graphics.h"
#include "../Material.h"
#include "../Effect.h"
#include "../../Core/EngineCore/Objects/Scene.h"

IDirect3DVertexBuffer9* Engine::Graphics::Line::s_vertexBuffer;
IDirect3DVertexDeclaration9* Engine::Graphics::Line::s_vertexDeclaration;


void Engine::Graphics::Line::drawLines(bool drawDebugLines)
{	
	if (writeToBuffer() && 
		Engine::Graphics::Effect::getEffect(
			Engine::Graphics::Material::getMaterial(
				materialName.c_str())->getEffectName())->setShaders()
		&& setUniforms())		
	{
		HRESULT vertexDeclerationResult = Engine::Graphics::GraphicsSystem::getDevice()->SetVertexDeclaration(s_vertexDeclaration);
		assert(SUCCEEDED(vertexDeclerationResult));
		HRESULT result;
		
		// There can be multiple streams of data feeding the display adaptor at the same time
		const unsigned int streamIndex = 1;
		// It's possible to start streaming data in the middle of a vertex buffer
		const unsigned int bufferOffset = 0;
		// The "stride" defines how large a single vertex is in the stream of data
		const unsigned int bufferStride = sizeof(float) * 7;
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
			D3DPT_LINELIST,
			0,
			static_cast<UINT>(mLineList.size()));

		//WindowsUtil::Assert(SUCCEEDED(result));
	}
}

bool Engine::Graphics::Line::createBuffer()
{
	if (!bufferInitialized)
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
		usage |= D3DUSAGE_WRITEONLY;

		/*
		Vertex Format - Similar to Vertex Attribute Pointer of OpenGL
		*/
		D3DVERTEXELEMENT9 vertexElements[] =
		{
			// Stream 0, POSITION( 3 floats == 12 bytes), Offset = 0
			{ 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },//Position
			{ 0, 12, D3DDECLTYPE_FLOAT4 , D3DDECLMETHOD_DEFAULT , D3DDECLUSAGE_COLOR, 0 },//Color
																				   // This will marker signals the end of the vertex declaration																					   
			D3DDECL_END()
		};

		HRESULT vertexDeclerationResult = Engine::Graphics::GraphicsSystem::getDevice()->CreateVertexDeclaration(vertexElements, &s_vertexDeclaration);

		if (!SUCCEEDED(vertexDeclerationResult))
		{
			WindowsUtil::Print("Direct3D failed to create a Direct3D9 vertex declaration");
			return false;
		}


		// Create a vertex buffer
		/*Need two vertex Attribute
		(3 position floats and 4 color floats)
		start and end point
		*/
		const unsigned int bufferSize = static_cast<const unsigned int>(sizeof(float) * 14 * 256);

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
		bufferInitialized = true;
	}
	return true;

}

bool Engine::Graphics::Line::writeToBuffer()
{
	if (!vertexBufferInitalized)
	{
		float *vertexData;
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

		float *data = new float[sizeof(float) * 14 * mLineList.size()];
		for (int i = 0; i < mLineList.size(); i++)
		{
			//StartPoint
			data[i + 0] = mLineList[i]->mLineStruct.startPoint.x;
			data[i + 1] = mLineList[i]->mLineStruct.startPoint.y;
			data[i + 2] = mLineList[i]->mLineStruct.startPoint.z;
			data[i + 3] = mLineList[i]->mLineStruct.color.r;
			data[i + 4] = mLineList[i]->mLineStruct.color.g;
			data[i + 5] = mLineList[i]->mLineStruct.color.b;
			data[i + 6] = mLineList[i]->mLineStruct.color.a;

			//EndPoint
			data[i + 7] = mLineList[i]->mLineStruct.endPoint.x;
			data[i + 8] = mLineList[i]->mLineStruct.endPoint.y;
			data[i + 9] = mLineList[i]->mLineStruct.endPoint.z;
			data[i + 10] = mLineList[i]->mLineStruct.color.r;
			data[i + 11] = mLineList[i]->mLineStruct.color.g;
			data[i + 12] = mLineList[i]->mLineStruct.color.b;
			data[i + 13] = mLineList[i]->mLineStruct.color.a;
		}

		memcpy(vertexData, data, sizeof(float) * 14 * mLineList.size());
		// unlockeing the buffer for use
		const HRESULT vertexBufferunlockResult = s_vertexBuffer->Unlock();
		if (FAILED(vertexBufferunlockResult))
		{
			WindowsUtil::Print("Direct3D failed to unlock the vertex buffer");
			return false;
		}
		vertexBufferInitalized = true;
	}
	
	return true;
}


bool Engine::Graphics::Line::setUniforms()
{
	SharedPointer<Scene> activeScene = Scene::getRenderableScene();
	SharedPointer<Camera> tempCamera = activeScene->getActiveCamera();

	if (!tempCamera.isNull())
	{
		Transformation cameraTransformation = tempCamera->getTransformation();
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
			Math::cMatrix_transformation::CreateWorldToViewTransform(
				cameraTransformation.mOrientation,
				cameraTransformation.mPositionOffset);
		worldToView->setUniformValue(worldToViewValues);


		Graphics::UniformValues viewToScreenValues;
		viewToScreenValues.matrixValue.Type = Graphics::ViewToScreen;
		viewToScreenValues.matrixValue.matrix =
			Math::cMatrix_transformation::CreateViewToScreenTransform(
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





