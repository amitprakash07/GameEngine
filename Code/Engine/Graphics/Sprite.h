#ifndef __SPRITE_H
#define __SPRITE_H

#include "../Core/EngineCore/Objects/Object.h"
#include "../Core/Utilities/SharedPointer.h"
#include "typedefs.h"
#include "../Core/Maths/Vector3.h"
#include "../Core/Maths/Vector2.h"

#ifdef PLATFORM_OPEN_GL
#include "../../Externals/OpenGLExtensions/OpenGlExtensions.h"
#elif PLATFORM_D3D
#include <d3d9.h>
#endif

namespace Engine
{
	struct vertexTexture
	{
		Math::Vector3 position;
		Math::Vector2 texture;
	};
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
			Math::Transform getTransform() override { return Math::Transform(); }
			uint8_t sliceSprite(uint8_t i_rows, uint8_t i_columns);
			void setCellToRender(uint8_t cellToRender);
			bool isMultiple() const;
			void setTransform(Engine::Math::Vector3,
				Engine::Math::Quaternion = Engine::Math::Quaternion()) override;
			void changeSpriteMaterial(std::string);
			void nextCell();
			void draw(bool debug = false) override;
			void debugObject(bool isDebug = false);
			bool isRenderable() const override;
			bool isDebugObject() const override;			
			~Sprite();
		private:
			Sprite(std::string spriteName,
				std::string materialName,
				float left,
				float right,
				float top,
				float bottom,
				Coordinate i_coordinate);
			bool isDebug;
			std::string mMaterial;
			std::string mSpriteName;
			float rectLeft;
			float rectRight;
			float rectTop;
			float rectBottom;
			bool multiple;
			uint8_t rows;
			uint8_t columns;
			uint8_t totalCells;
			uint8_t cellToRender;
			float URange;
			float VRange;
			bool createBuffers();
			bool writeToBuffer();
			void drawSprite();
			vertexTexture * vertexAttribute;
			vertexTexture*  getTextureAndVerticesData()const;
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
#endif

		};
	}
}

#endif