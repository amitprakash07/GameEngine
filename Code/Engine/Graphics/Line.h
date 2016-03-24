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
			static void AddLine(Engine::Math::Vector3 i_startPoint,
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
			void setObjectController(IObjectController *i_ObjectControlller) override;
		private:
			static std::vector<SharedPointer<Line>> mLineList;
			static bool setUniforms();
			Line();
			IObjectController* mObjectController;
			LineStruct mLineStruct;
			bool debugObject;
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