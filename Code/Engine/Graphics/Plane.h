#ifndef __PLANE_H
#define __PLANE_H


#include "../Core/EngineCore/Objects/Object.h"
#include "../Core/Utilities/SharedPointer.h"

#ifdef PLATFORM_OPEN_GL
#include "../../Externals/OpenGLExtensions/OpenGlExtensions.h"
#elif PLATFORM_D3D
#include <d3d9.h>
#endif

#include "../../Engine/Core/Utilities/IMessageHandler.h"
#include "Uniform.h"
#include "typedefs.h"

namespace Engine
{
	namespace Graphics
	{
		class Plane: public IMessageHandler, Object
		{
		public:
			static SharedPointer<Plane> CreatePlane(std::string iMaterialName);
			//Object Ovverriding functions			
			Math::Transform getTransform() override;
			void setTransform(Math::Vector3,
				Math::Quaternion = Math::Quaternion()) override;
			bool isDebugObject() const override;
			bool isRenderable() const override;
			void draw(bool drawDebugObject) override;			
			void updateObject() override;
			void setObjectController(IObjectController *)override;
			void setScale(float x = 1.0f, float y = 1.0f, float z = 1.0f) override;
			//IMessageHandler
			void HandleMessage(
				Engine::utils::StringHash &,
				RTTI* i_MessageSender, void* i_pMessageData) override;
			std::string getTypeInfo() const override { return ""; }
			bool isBothSameType(RTTI*, std::string) const override { return true; }
		private:
			Plane(std::string material_name);
			Math::Transform mTransform;
			std::string mMaterialName;
			bool createBuffer();
			IObjectController * mObjectController;
			Engine::Math::Vector3 scaleFactor;
			bool writeToBuffer();
			bool debugObject;
			VertexTextureNormal * vertexattribute;
			VertexTextureNormal* getVertexAttributeData();
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