#ifndef __TEXT_H
#define __TEXT_H
#include "../Core/EngineCore/Objects/Object.h"
#include "../../Engine/Core/Utilities/IMessageHandler.h"
#include "../../Externals/OpenGLExtensions/OpenGlExtensions.h"
#include <map>

namespace Engine
{
	namespace Graphics
	{
		class Text: public IMessageHandler, Object
		{
		public:
			static SharedPointer<Text> CreateText(
				std::string iMaterialName,
				std::string iFont,
				Math::Transform iTransform);
			void SetTextToRender(std::string iText);
			std::string GetText()const;
			//Object Overriding functions			
			Math::Transform getTransform() override;
			void setTransform(Math::Vector3,
				Math::Quaternion = Math::Quaternion()) override;
			void resetTransform() override {}
			bool isDebugObject() const override;
			bool isRenderable() const override;
			void draw(bool drawDebugObject) override;
			void setRenderable(bool iRenderable) override;
			void updateObject() override;
			void setObjectController(SharedPointer<IObjectController> )override;
			void setScale(float x = 1.0f, float y = 1.0f, float z = 1.0f) override;
			Math::Vector3 getScale() const override;
			Graphics::RGBAColor GetVertexColor() const override;
			void SetVertexColor(float iR, float iG, float iB, float iA) override;
			std::string getMaterialName() override;
			bool isCollidable() override;
			bool isPhysicsEnabled() override;
			void enableCollision(bool) override;
			void enablePhysics(bool) override;
			void castShadow(bool, Graphics::ShadowMethod) override;
			bool castingShadowEnabled() override;
			void receiveShadow(bool) override;
			bool receivingShadowEnabled() override;
			bool IsPlayer() override;
			void setPlayer(bool) override;
			void setObjectType(ObjectType iObjectType) override;
			ObjectType getObjectType() override;
			void SetMaterial(std::string iMaterialName) override;
			bool isSSAOEnabled() override;
			void EnableSSAO(bool iRequest) override;
			//IMessageHandler
			void HandleMessage(
				Engine::utils::StringHash &,
				SharedPointer<RTTI> i_MessageSender, void* i_pMessageData) override;
			std::string getTypeInfo() const override { return ""; }
			bool isBothSameType(SharedPointer<RTTI>, std::string) const override { return true; }			
		private:
			struct Character {
#ifdef PLATFORM_OPEN_GL
				GLuint TextureID; // ID handle of the glyph texture
				/*
					size.x = glyph.width
					size.y = glyph.rows
				*/
				Engine::Math::Vector2 Size; // Size of glyph
				/*
					Bearing.x = glyph.left
					Bearing.y = glyph top
				*/
				Engine::Math::Vector2 Bearing; // Offset from baseline to left/top of glyph
				Engine::Math::Vector2 Advance; // Offset to advance to next glyph
				
#endif
			};
			static std::map<std::string, std::map<GLchar, Character>> Characters;
			static std::map<std::string, bool> isCharacterTextureInitialized;
			static bool InitializeTexturesForCharacters(std::string iFont);
			static bool isFontTextureLoaded(std::string iFontName);
			void InitializeText();
			Text();
			RGBAColor mColor;
			SharedPointer<IObjectController> mObjectController;
			Math::Vector3 mScale;
			Math::Transform mTransform;
			std::string mEffectFileName;
			std::string mFontName;
			std::string textToBeRendered;
			GLuint vertexBuffer;
			GLuint vertexArray;
			GLuint textColor;
		};
	}
}

#endif