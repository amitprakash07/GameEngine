#include "../Sprite.h"
#include "../../Core/Maths/Functions.h"
#include "../../Windows/WindowsFunctions.h"
#include "../../Core/EngineCore/EngineCore.h"
#include "../Graphics.h"

Engine::Graphics::Sprite::Sprite(std::string iSpriteName,
	std::string iMaterialName,
	float left, 
	float right, 
	float top, 
	float bottom, 
	Coordinate i_coordinate)
{

	//Might need to change as OpenGL screen coordinate 
	//system is different than DirectX
	int windowWidth = EngineCore::getWindowingSystem()->getWindowWidth() / 2;
	int windowHeight = EngineCore::getWindowingSystem()->getWindowHeight() / 2;

	switch (i_coordinate)
	{
	case VIEWPORT_COORDINATE:
		left = Math::scaleAndBias(left, -windowWidth, windowWidth, -1, 1);
		right = Math::scaleAndBias(right, -windowWidth, windowWidth, -1, 1);
		top = Math::scaleAndBias(top, -windowHeight, windowHeight, -1, 1);
		bottom = Math::scaleAndBias(bottom, static_cast<float>(-windowHeight),
			static_cast<float>(windowHeight), -1.0f, 1.0f);
		break;
	case TEXTURE_COORDINATE:
		left = Math::scaleAndBias(left, 0, 1, -1, 1);
		right = Math::scaleAndBias(right, 0, 1, -1, 1);
		top = Math::scaleAndBias(top, 0, 1, -1, 1);
		bottom = Math::scaleAndBias(bottom, 0, 1, -1, 1);
		break;
	case SCREEN_COORDINATE:
		break;
	}
	rectLeft = left;
	rectRight = right;
	rectTop = top;
	rectBottom = bottom;
	mSpriteName = iSpriteName;
	mMaterial = iMaterialName;
	s_vertexArrayID = 0;
	vertexBufferId = 0;
	mObjectController = nullptr;
}


bool Engine::Graphics::Sprite::createVertexArray()
{
	//Stub -- Need to complete this
	return true;
}


bool Engine::Graphics::Sprite::createBuffers()
{
	return (createVertexArray());
}

bool Engine::Graphics::Sprite::writeToBuffer() const
{
	return true;
}


