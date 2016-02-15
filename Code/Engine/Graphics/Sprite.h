#ifndef __SPRITE_H
#define __SPRITE_H

#include "../Core/EngineCore/Objects/Object.h"
#include "../Core/Utilities/SharedPointer.h"
#include "typedefs.h"


#ifdef PLATFORM_OPEN_GL
#include "../../Externals/OpenGLExtensions/OpenGlExtensions.h"
#elif PLATFORM_D3D
#include <d3d9.h>
#endif

namespace Engine
{
	namespace Graphics
	{
		class Sprite :public Engine::Object
		{
		public:
			static SharedPointer<Sprite> CreateSprite(
				std::string spriteName,
				std::string materialName,
				float left,
				float right,
				float top,
				float bottom,
				Coordinate i_coordinate = SCREEN_COORDINATE);
			Transformation getTransformation() override { return Transformation(); }
			void setTransformation(Engine::Math::cVector,
				Engine::Math::cQuaternion = Engine::Math::cQuaternion()) override;
			void changeSpriteMaterial(std::string);
			void draw() override;
			~Sprite();
		private:
			Sprite(std::string spriteName,
				std::string materialName,
				float left,
				float right,
				float top,
				float bottom,
				Coordinate i_coordinate);
			std::string mMaterial;
			std::string mSpriteName;
			float rectLeft;
			float rectRight;
			float rectTop;
			float rectBottom;
			bool createBuffers();
			bool writeToBuffer() const;
#ifdef PLATFORM_OPEN_GL
			GLuint s_vertexArrayID;
			GLuint vertexBufferId;
			bool createVertexArray();
#elif PLATFORM_D3D
			IDirect3DVertexBuffer9* s_vertexBuffer;
			IDirect3DVertexDeclaration9* s_vertexDeclaration;
			bool createVertexBuffer();
#endif

		};
	}
}

#endif