#ifndef __SKY_BOX_H
#define __SKY_BOX_H

#include "../Core/EngineCore/Objects/Object.h"
#include "../Core/Utilities/SharedPointer.h"

#ifdef PLATFORM_OPEN_GL
#include "../../Externals/OpenGLExtensions/OpenGlExtensions.h"
#elif PLATFORM_D3D
#include <d3d9.h>
#endif

namespace Engine
{
	namespace Graphics
	{
		class SkyBox:public Engine::Object
		{
		public:
			static void CreateSkyBox(std::string i_MaterialName);
			static SharedPointer<SkyBox> getSkyBox();
			Math::Transformation getTransformation() override;
			void setTransformation(Math::Vector3,
				Math::Quaternion = Math::Quaternion()) override;
			bool isDebugObject() const override;
			bool isRenderable() const override;
			void draw(bool drawDebugObject) override;
			void setMaterial(std::string newMaterialName);
			bool isSkyBoxAvailableIntialized()const;
		private:
			static SharedPointer<SkyBox> mSkyBox;
			SkyBox(std::string material_Name);
			Math::Transformation stubTransform;
			std::string mMaterialName;
			bool createBuffer();	
			bool isSkyBoxAvailable;
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
