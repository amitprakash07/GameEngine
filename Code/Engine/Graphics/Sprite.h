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
			
			uint8_t sliceSprite(uint8_t i_rows, uint8_t i_columns);
			void setCellToRender(uint8_t cellToRender);
			bool isMultiple() const;
			void changeSpriteMaterial(std::string);
			void nextCell();
			Math::Transform getTransform() override { return Math::Transform(); }
			void setTransform(Engine::Math::Vector3,
				Engine::Math::Quaternion = Engine::Math::Quaternion()) override;
			void resetTransform() override {}
			void draw(bool debug = false) override;
			void debugObject(bool isDebug = false);
			void setRenderable(bool iRenderable) override { /*to-do*/ }
			bool isRenderable() const override;
			bool isDebugObject() const override;	
			void updateObject() override;
			void setObjectController(IObjectController* objectController) override;
			void setScale(float x = 1.0f, float y = 1.0f, float z = 1.0f) override{}
			Math::Vector3 getScale() const override { return Math::Vector3(0.0f);/*Stub*/ }
			Graphics::RGBAColor GetVertexColor() const override { return Graphics::RGBAColor(0.0f); }
			void SetVertexColor(float iR, float iG, float iB, float iA) override{}
			std::string getMaterialName() override { return mMaterial; }
			bool isCollidable() override;
			bool isPhysicsEnabled() override;
			void enableCollision(bool) override;
			void enablePhysics(bool) override;
			void castShadow(bool, Graphics::ShadowMethod) override;
			bool castingShadowEnabled() override;
			void receiveShadow(bool) override;
			bool receivingShadowEnabled() override;
			bool IsPlayer() override;
			void setPlayer(bool i_isPlayer) override;
			ObjectType getObjectType() override;
			void setObjectType(ObjectType iObjectType) override;
			void SetMaterial(std::string iMaterialName) override;
			bool isSSAOEnabled() override { return false; }
			void EnableSSAO(bool iRequest) override {}
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
			uint32_t spriteDelay;
			uint32_t currentTick;
			float URange;
			float VRange;
			bool createBuffers();
			bool writeToBuffer();
			void drawSprite();
			vertexTexture * vertexAttribute;
			vertexTexture*  getTextureAndVerticesData()const;
			IObjectController * mObjectController;
			bool isPlayer;
			ObjectType mObjectType;
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