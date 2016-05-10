#include "Text.h"
#include "../../Engine/Core/Utilities/IObjectController.h"
#include "../Windows/WindowsFunctions.h"
#include "../Core/EngineCore/EngineCore.h"
#include "Effect.h"


std::map<std::string, std::map<GLchar, Engine::Graphics::Text::Character>>
Engine::Graphics::Text::Characters;
std::map<std::string, bool> Engine::Graphics::Text::isCharacterTextureInitialized;


void Engine::Graphics::Text::SetMaterial(std::string iMaterialName)
{
	//Stub
}


bool Engine::Graphics::Text::isSSAOEnabled()
{
	return false;
}

void Engine::Graphics::Text::EnableSSAO(bool iRequest)
{
	//Stub
}

std::string Engine::Graphics::Text::GetText() const
{
	return textToBeRendered;
}

void Engine::Graphics::Text::SetTextToRender(std::string iText)
{
	textToBeRendered = iText;
}



Engine::Graphics::Text::Text()
{
	mColor = RGBAColor();
	mObjectController = nullptr;
	mScale = Math::Vector3();
	mTransform = Math::Transform();
	vertexBuffer = -1;
	vertexArray = -1;
}

Engine::SharedPointer<Engine::Graphics::Text>
Engine::Graphics::Text::CreateText(
	std::string iEffectFileName,
	std::string iFont,
	Math::Transform iTransform)
{
	SharedPointer<Text> tempText =
		SharedPointer<Text>(new Text(), "Engine::Graphics::Text");
	if (!isFontTextureLoaded(iFont) && InitializeTexturesForCharacters(iFont))
	{
		WindowsUtil::displayToOutPutWindow("Font Initialized");
	}

	iEffectFileName = Engine::EngineCore::getEffectFolderPath()
		+ iEffectFileName;
	tempText->mEffectFileName = iEffectFileName;
	tempText->mTransform = iTransform;
	tempText->mFontName = iFont;
	tempText->InitializeText();
	return tempText;
}


bool Engine::Graphics::Text::isFontTextureLoaded(std::string iFontName)
{
	for (std::map<std::string, bool>::iterator i = isCharacterTextureInitialized.begin();
		i != isCharacterTextureInitialized.end(); ++i)
	{
		if (i->first == iFontName)
			return i->second;
	}
	return false;
}


Engine::Graphics::RGBAColor Engine::Graphics::Text::GetVertexColor() const
{
	return mColor;
}


void Engine::Graphics::Text::HandleMessage(Engine::utils::StringHash& i_message,
	RTTI* i_MessageSender, void* i_pMessageData)
{
	if (i_MessageSender != nullptr)
	{
		if (i_MessageSender != nullptr && Engine::utils::StringHash("UpdateObject") == i_message && mObjectController)
			mObjectController->updateObject(*this, *reinterpret_cast<Engine::typedefs::ActionWithKeyBound*>(i_pMessageData));
	}
}


bool Engine::Graphics::Text::IsPlayer()
{
	return false;
}


void Engine::Graphics::Text::SetVertexColor(float iR, float iG, float iB, float iA)
{
	mColor = RGBAColor(iR, iG, iB, iA);
}

void Engine::Graphics::Text::castShadow(bool, Graphics::ShadowMethod)
{
	//Stub
}

bool Engine::Graphics::Text::castingShadowEnabled()
{
	return false;
}

void Engine::Graphics::Text::enableCollision(bool)
{
	//Stub
}

void Engine::Graphics::Text::enablePhysics(bool)
{
	//Stub
}


std::string Engine::Graphics::Text::getMaterialName()
{
	return "None";
}

Engine::ObjectType Engine::Graphics::Text::getObjectType()
{
	return ObjectType::NONE;
}

Engine::Math::Vector3 Engine::Graphics::Text::getScale() const
{
	return mScale;
}


Engine::Math::Transform Engine::Graphics::Text::getTransform()
{
	return mTransform;
}


bool Engine::Graphics::Text::isCollidable()
{
	return false;
}

bool Engine::Graphics::Text::isDebugObject() const
{
	return false;
}

bool Engine::Graphics::Text::isPhysicsEnabled()
{
	return false;
}

bool Engine::Graphics::Text::isRenderable() const
{
	return true;
}


void Engine::Graphics::Text::receiveShadow(bool)
{
	//Stub
}


bool Engine::Graphics::Text::receivingShadowEnabled()
{
	return false;
}


void Engine::Graphics::Text::setObjectController(IObjectController* iObjectController)
{
	if (iObjectController)
		mObjectController = iObjectController;
}

void Engine::Graphics::Text::setObjectType(ObjectType iObjectType)
{
	//Stub
}

void Engine::Graphics::Text::setPlayer(bool)
{
	//Stub
}

void Engine::Graphics::Text::setRenderable(bool iRenderable)
{
	//Stub
}

void Engine::Graphics::Text::setScale(float x, float y, float z)
{
	mScale = Math::Vector3(x, y, z);
}

void Engine::Graphics::Text::setTransform(
	Math::Vector3 iPosition, Math::Quaternion iOrientation)
{
	mTransform = Math::Transform(iPosition, iOrientation);
}

void Engine::Graphics::Text::updateObject()
{
	typedefs::ActionWithKeyBound action;
	action.action = typedefs::Default;
	action.keyVal = 0x00;
	if (mObjectController)
		mObjectController->updateObject(*this, action);
}