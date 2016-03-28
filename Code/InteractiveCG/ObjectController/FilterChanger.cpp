#include "FilterChanger.h"
#include "../../../Code/Engine/Core/EngineCore/Objects/MeshObject.h"
#include "../../../Code/Engine/Graphics/Material.h"
#include "../../../Code/Engine/Graphics/Texture.h"
#include "../../../Code/Engine/Core/Utilities/SharedPointer.h"


void Application::TextureFilterChanger::updateObject(Engine::Object& iObject, 
	Engine::typedefs::ActionWithKeyBound iAction)
{
	Engine::SharedPointer<Engine::Graphics::Material> tempMaterial
		= Engine::Graphics::Material::getMaterial(iObject.getMaterialName().c_str());
	switch (iAction.keyVal)
	{
	case 0x4c://L Key
		Engine::Graphics::Texture::getTexture(
			tempMaterial->getMap(
				Engine::Graphics::ALBEDO,
				Engine::Graphics::Fragment).c_str())->changeTextureFilter(
					Engine::Graphics::MinFilter::LINEAR_LINEAR,
					Engine::Graphics::MagFilter::LINEAR);
		break;
	case 0x4e: //N key
		Engine::Graphics::Texture::getTexture(
			tempMaterial->getMap(
				Engine::Graphics::ALBEDO,
				Engine::Graphics::Fragment).c_str())->changeTextureFilter(
					Engine::Graphics::MinFilter::NEAREST_LINEAR,
					Engine::Graphics::MagFilter::NEAREST);
		break;
	default:
		break;

	}
}