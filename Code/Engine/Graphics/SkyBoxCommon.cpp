#include "SkyBox.h"
#include "../Graphics/Material.h"
#include "../Core/EngineCore/EngineCore.h"


Engine::SharedPointer<Engine::Graphics::SkyBox>
	Engine::Graphics::SkyBox::mSkyBox;


void Engine::Graphics::SkyBox::CreateSkyBox(std::string i_materialName)
{
	if(mSkyBox.isNull())
	{
		i_materialName = Engine::EngineCore::getMaterialFolderPath() + i_materialName;
		SharedPointer<SkyBox> tempSkyBox = 
			SharedPointer<SkyBox>(new SkyBox(i_materialName), "Engine::Graphics::SkyBox");
		mSkyBox = tempSkyBox;
		Engine::Graphics::Material::addMaterialToList(i_materialName.c_str());
		if(mSkyBox->createBuffer())
			mSkyBox->isSkyBoxAvailable = true;
	}
}

bool Engine::Graphics::SkyBox::isSkyBoxAvailableIntialized() const
{
	return isSkyBoxAvailable;
}

Engine::Math::Transform Engine::Graphics::SkyBox::getTransform()
{
	return stubTransform;
}

Engine::SharedPointer<Engine::Graphics::SkyBox> Engine::Graphics::SkyBox::getSkyBox()
{
	return mSkyBox;
}

bool Engine::Graphics::SkyBox::isDebugObject() const
{
	return false;
}

void Engine::Graphics::SkyBox::setMaterial(std::string newMaterialName)
{
	mMaterialName = newMaterialName;
}

bool Engine::Graphics::SkyBox::isRenderable() const
{
	return true;
}

void Engine::Graphics::SkyBox::setTransform(Math::Vector3, Math::Quaternion)
{
	
}












