#ifndef __MESH_H
#define __MESH_H
#pragma warning(disable :4006)
#ifdef PLATFORM_OPEN_GL
#include "../../Externals/OpenGLExtensions/OpenGlExtensions.h"
#elif PLATFORM_D3D
#include <d3d9.h>
#endif

#include <stdint.h>
#include <vector>
#include <map>
#include "../Core/Utilities/SharedPointer.h"
#include "typedefs.h"
#include "../Graphics/Uniform.h"

namespace Engine
{
	namespace Graphics
	{
		class Mesh :public RTTI
		{
		public:
			static bool addToMeshList(std::string);
			static SharedPointer<Mesh> getMesh(std::string);
			static void deleteAllMesh();
			bool drawMesh(bool wireFrame = false);
			bool LoadMesh();
			vertex* getVertex() const;
			uint32_t* getIndices() const;
			void setWinding(winding);
			winding getWinding() const;
			std::string getMeshFileName() const;
			std::string getTypeInfo() const override { return ""; }
			bool isBothSameType(RTTI*, std::string) const override { return true; }			
			~Mesh();
		private:
			static std::map<std::string, SharedPointer<Mesh>> meshList;
			std::map<std::string, SharedPointer<Engine::Graphics::Uniform>> uniformNames;
			vertex *mVertex;
			uint32_t *mIndices;
			winding mWinding;
			int triangleCount;
			int vertexCount;
			std::string meshFileName;
			static bool isMeshExist(std::string);
			Mesh(std::string);
			bool createBuffers();
#ifdef PLATFORM_OPEN_GL
			GLuint s_vertexArrayID;
			GLuint vertexBufferId;
			GLuint indexBufferId;
			bool createVertexArray();
#elif PLATFORM_D3D
			IDirect3DVertexBuffer9* s_vertexBuffer;
			IDirect3DIndexBuffer9* s_indexBuffer;
			IDirect3DVertexDeclaration9* s_vertexDeclaration;
			bool createVertexBuffer();
			bool createIndexBuffer();
#endif

		};
	}
}
#endif