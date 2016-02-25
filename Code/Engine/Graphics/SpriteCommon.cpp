#include "Sprite.h"
#include "../Windows/WindowsFunctions.h"
#include "../Core/EngineCore/EngineCore.h"
#include "Material.h"
#include "../Core/Maths/Functions.h"

Engine::SharedPointer<Engine::Graphics::Sprite>
Engine::Graphics::Sprite::CreateSprite(std::string iSpriteName,
	std::string iMaterialName,
	float left,
	float right,
	float top,
	float bottom,
	Coordinate i_coordinate)
{
	int windowWidth = EngineCore::getWindowingSystem()->getWindowWidth() / 2;
	int windowHeight = EngineCore::getWindowingSystem()->getWindowHeight() / 2;

	switch (i_coordinate)
	{
	case VIEWPORT_COORDINATE:
		WindowsUtil::Assert(Math::InRange(left, -windowWidth, windowWidth)
			&& Math::InRange(right, -windowWidth, windowWidth)
			&& Math::InRange(top, -windowHeight, windowHeight)
			&& Math::InRange(bottom, -windowHeight, windowHeight),
			"Sprite position should be in within viewport window");
		break;
	case SCREEN_COORDINATE:
		WindowsUtil::Assert(Math::InRange(left, -1, 1)
			&& Math::InRange(right, -1, 1)
			&& Math::InRange(top, -1, 1)
			&& Math::InRange(bottom, -1, 1),
			"Sprite position should be in screen coordinate");
		break;
	case TEXTURE_COORDINATE:
		WindowsUtil::Assert(Math::InRange(left, 0, 1)
			&& Math::InRange(right, 0, 1)
			&& Math::InRange(top, 0, 1)
			&& Math::InRange(bottom, 0, 1),
			"Sprite position should be in texture coordinate");
		break;
	}


	std::stringstream errormessage;

	if (!iSpriteName.empty() && !iMaterialName.empty())
	{
		if (Engine::Graphics::Material::addMaterialToList(iMaterialName.c_str()))
		{
			SharedPointer<Sprite> sprite(new Sprite(iSpriteName, iMaterialName,
				left, right, top, bottom, i_coordinate),
				"Engine::Graphics::Sprite");
			if (!sprite->createBuffers())
			{
				errormessage << "Unable to Create buffer for the sprite";
				WindowsUtil::Print(errormessage.str(), __FILE__);
				sprite.deleteObject();
			}
		}
		else
		{
			errormessage << "Something went wrong while loading sprite material";
			WindowsUtil::Print(errormessage.str(), __FILE__);
		}
	}
	else
	{
		errormessage << "Sprite Name or Material Name is empty";
		WindowsUtil::Print(errormessage.str(), __FILE__);
	}

	return SharedPointer<Engine::Graphics::Sprite>();
}

void Engine::Graphics::Sprite::changeSpriteMaterial(std::string iMaterial)
{
	if (!Engine::Graphics::Material::isMaterialExist(iMaterial.c_str()))
		Engine::Graphics::Material::addMaterialToList(iMaterial.c_str());
	mMaterial = iMaterial;
}


//Stub - May be need to fix but later
void Engine::Graphics::Sprite::setTransformation(Engine::Math::Vector3, Engine::Math::Quaternion)
{

}
