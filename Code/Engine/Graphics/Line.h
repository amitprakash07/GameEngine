#ifndef __LINE_H
#define __LINE_H

#include "../Core/EngineCore/Objects/Object.h"
#include "../Core/Utilities/SharedPointer.h"
#include "typedefs.h"
#include <vector>

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
			Engine::Maths::Point3 startPoint;
			Engine::Maths::Point3 endPoint;
			RGBAColor color;
		};

		class Line :public Object
		{
		public:
			static void drawLines(bool drawDebugLines);
			static void AddLine(Engine::Maths::Point3 i_startPoint,
				Engine::Maths::Point3 i_endPoint,
				RGBAColor iLineColor);
			Transformation getTransformation() override;
			void setTransformation(Math::cVector,
				Math::cQuaternion = Math::cQuaternion()) override;
			bool isDebugObject() const override;
			bool isRenderable() const override;
			void draw(bool drawDebugObject) override;
			static bool containsDebugLine();
		private:
			static std::vector<SharedPointer<Line>> mLineList;
			Line();
			LineStruct mLineStruct;
			bool debugObject;
			static bool createBuffer();
			static bool writeToBuffer();
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