#ifndef __SKY_BOX_H
#define __SKY_BOX_H

#include "../Core/EngineCore/Objects/Object.h"
#include "../Core/Utilities/SharedPointer.h"

#ifdef PLATFORM_OPEN_GL
#include "../../Externals/OpenGLExtensions/OpenGlExtensions.h"
#elif PLATFORM_D3D
#include <d3d9.h>
#endif

#include "../../Engine/Core/Utilities/IMessageHandler.h"
#include <map>

namespace Engine
{
	namespace Graphics
	{
		class SkyBox:public IMessageHandler,Engine::Object
		{
		public:
			static SharedPointer<SkyBox> CreateSkyBox(std::string i_MaterialName);
			static SharedPointer<SkyBox> getCurrentSkyBox();
			static SharedPointer<SkyBox> getSkyBox(std::string);
			static SharedPointer<SkyBox> getSkyBox(int index);
			Math::Transform getTransform() override;
			void setTransform(Math::Vector3,
				Math::Quaternion = Math::Quaternion()) override;
			bool isDebugObject() const override;
			bool isRenderable() const override;
			void draw(bool drawDebugObject) override;
			void setMaterial(std::string newMaterialName);
			bool isSkyBoxAvailableIntialized()const;
			void updateObject() override;
			void setObjectController(IObjectController *)override;
			void setCurrentSkyBox();
			static bool isSkyBoxExist(std::string materialName);
			void HandleMessage(
				Engine::utils::StringHash &,
				RTTI* i_MessageSender, void* i_pMessageData) override;
			std::string getTypeInfo() const override { return ""; }
			bool isBothSameType(RTTI*, std::string) const override { return true; }
		private:
			static std::map<std::string, SharedPointer<SkyBox>> mSkyBoxList;
			static bool isSkyBoxAvailable;			
			SkyBox(std::string material_Name);
			Math::Transform stubTransform;
			std::string mMaterialName;
			bool createBuffer();				
			IObjectController * mObjectController;
			bool isCurrent;
			static void deactivateAll();
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
