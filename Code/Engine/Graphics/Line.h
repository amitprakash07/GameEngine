#ifndef __LINE_H
#define __LINE_H

#include "../Core/EngineCore/Objects/Object.h"
#include "../Core/Utilities/SharedPointer.h"
#include "typedefs.h"
#include <vector>
#include "../Core/Maths/Vector3.h"

#ifdef PLATFORM_OPEN_GL
#include "../../Externals/OpenGLExtensions/OpenGlExtensions.h"
#elif PLATFORM_D3D
#include <d3d9.h>
#endif

namespace Engine
{
	namespace Graphics
	{
		struct LineStruct
		{
			Engine::Math::Vector3 startPoint; //12 bytes
			Engine::Math::Vector3 endPoint; //12 bytes
			RGBAColor color; //16 bytes
		};

		class Line :public Object
		{
		public:
			static void drawLines(bool drawDebugLines);
			static SharedPointer<Line> AddLine(Engine::Math::Vector3 i_startPoint,
				Engine::Math::Vector3 i_endPoint,
				RGBAColor iLineColor);
			static bool containsDebugLine();
			static void setMaterialName(std::string iMaterialName);
			static uint8_t getLineCounts();
			Math::Transform getTransform() override;
			void setTransform(Math::Vector3,
				Math::Quaternion = Math::Quaternion()) override;
			void resetTransform() override;
			bool isDebugObject() const override;
			bool isRenderable() const override;
			void draw(bool drawDebugObject) override;	
			void updateObject() override;
			void setRenderable(bool iRenderable) override { /*to-do*/ }
			void setScale(float x = 1.0f, float y = 1.0f, float z = 1.0f) override{}
			Math::Vector3 getScale() const override { return Math::Vector3(0.0f);/*Stub*/ }
			Graphics::RGBAColor GetVertexColor() const override { return Graphics::RGBAColor(0.0f); }
			void SetVertexColor(float iR, float iG, float iB, float iA) override{}
			void setObjectController(SharedPointer<IObjectController> i_ObjectControlller) override;
			std::string getMaterialName() override { return materialName; }
			bool isCollidable() override;
			bool isPhysicsEnabled() override;
			void enableCollision(bool) override;
			void enablePhysics(bool) override;
			void castShadow(bool, Graphics::ShadowMethod) override;
			bool castingShadowEnabled() override;
			void receiveShadow(bool) override;
			bool receivingShadowEnabled() override;
			bool IsPlayer() override { return false; }
			void setPlayer(bool) override{}
			void setObjectType(ObjectType iObjectType) override;
			ObjectType getObjectType() override;
			void SetMaterial(std::string iMaterialName) override;
			bool isSSAOEnabled() override { return false; }
			void EnableSSAO(bool iRequest) override {}
			LineStruct mLineStruct;
		private:
			static std::vector<SharedPointer<Line>> mLineList;
			static bool setUniforms();
			Line();
			SharedPointer<IObjectController> mObjectController;			
			bool debugObject;
			ObjectType mObjectType;
			static std::string materialName;
			static bool createBuffer();
			static bool writeToBuffer();
			static bool bufferInitialized;
			static bool vertexBufferInitalized;
#ifdef PLATFORM_OPEN_GL
			static 	GLuint s_vertexArrayID;
			static GLuint vertexBufferId;
#elif PLATFORM_D3D
			static 	IDirect3DVertexBuffer9* s_vertexBuffer;
			static IDirect3DVertexDeclaration9* s_vertexDeclaration;
#endif
		};
	}
}

#endif