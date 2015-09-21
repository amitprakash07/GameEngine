#include "../Mesh.h"
#include "../Graphics.h"
#include <assert.h>
#include <stdint.h>

namespace Engine
{
	namespace Graphics
	{
		IDirect3DVertexBuffer9* Mesh::s_vertexBuffer = nullptr;
		IDirect3DIndexBuffer9* Mesh::s_indexBuffer = nullptr;
		IDirect3DVertexDeclaration9* Mesh::s_vertexDeclaration = nullptr;
		bool CreateIndexBuffer();
		bool CreateVertexBuffer();
		HRESULT GetVertexProcessingUsage(DWORD& o_usage);
		}
}



bool Engine::Graphics::Mesh::drawMesh()
{
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
		const unsigned int primitiveCountToRender = 2; // EAE6320_TODO;	// How many triangles will be drawn?

		result = Engine::Graphics::GraphicsSystem::getDevice()->DrawIndexedPrimitive(primitiveType,
			indexOfFirstVertexToRender, indexOfFirstVertexToRender, vertexCountToRender,
			indexOfFirstIndexToUse, primitiveCountToRender);
		
		return(SUCCEEDED(result));	
}

IDirect3DVertexBuffer9* Engine::Graphics::Mesh::getVertexBuffer()
{
	return s_vertexBuffer;
}

IDirect3DIndexBuffer9* Engine::Graphics::Mesh::getIndexBuffer()
{
	return s_indexBuffer;
}

IDirect3DVertexDeclaration9* Engine::Graphics::Mesh::getVertexDeclaration()
{
	return s_vertexDeclaration;
}

void Engine::Graphics::Mesh::setVertexBuffer(IDirect3DVertexBuffer9* i_vertexBuffer)
{
	s_vertexBuffer = i_vertexBuffer;
}

void Engine::Graphics::Mesh::setIndexBuffer(IDirect3DIndexBuffer9* i_indexBuffer)
{
	s_indexBuffer = i_indexBuffer;
}


void Engine::Graphics::Mesh::setVertexDeclaration(IDirect3DVertexDeclaration9* i_vertexDeclaration)
{
	s_vertexDeclaration = i_vertexDeclaration;
}

