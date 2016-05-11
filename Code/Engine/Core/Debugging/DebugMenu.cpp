#include "DebugMenu.h"
#include "../EngineCore/EngineCore.h"
#include "../../Core/Utilities/IObjectController.h"
#include "../../Graphics/Text.h"



void Engine::Debug::DebugMenu::HandleMessage(
	Engine::utils::StringHash& i_message,
	SharedPointer<RTTI> i_MessageSender,
	void* i_pMessageData)
{
	if (!i_MessageSender.isNull() && Engine::utils::StringHash("DebugMenuHandler") == i_message)
	{
		Engine::typedefs::ActionWithKeyBound keyBoardInput =
			*reinterpret_cast<typedefs::ActionWithKeyBound*>(i_pMessageData);
		switch (keyBoardInput.keyVal)
		{
		case VK_SPACE:
		{
			if (isActive)
			{
				if(mDebugMenuAssociatedObjectList[currentlySelected].mType == CheckBox ||
					mDebugMenuAssociatedObjectList[currentlySelected].mType == Button)
				{
					switch(mDebugMenuAssociatedObjectList[currentlySelected].mType)
					{
					case CheckBox:					
						mDebugMenuAssociatedObjectList[currentlySelected].mData.checkBoxStatus =
							!mDebugMenuAssociatedObjectList[currentlySelected].mData.checkBoxStatus;
						mDebugMenuAssociatedObjectList[currentlySelected].mAssociatedObject->setRenderable(
								mDebugMenuAssociatedObjectList[currentlySelected].mData.checkBoxStatus);
							if(mDebugMenuAssociatedObjectList[currentlySelected].mData.checkBoxStatus)
								mDebugMenuAssociatedObjectList[currentlySelected].mUIElement->SetTextToRender("[X]");
							else
								mDebugMenuAssociatedObjectList[currentlySelected].mUIElement->SetTextToRender("[ ]");
						break;
					case Button:
						mDebugMenuAssociatedObjectList[currentlySelected].mData.buttonStatus =
							!mDebugMenuAssociatedObjectList[currentlySelected].mData.buttonStatus;
						if (mDebugMenuAssociatedObjectList[currentlySelected].mData.buttonStatus)
						{
							mDebugMenuAssociatedObjectList[currentlySelected].mUIElement->SetTextToRender("ON");
							mDebugMenuAssociatedObjectList[currentlySelected].mAssociatedObject->setScale(1.0f, 1.0f, 1.0f);
						}
						else
							mDebugMenuAssociatedObjectList[currentlySelected].mUIElement->SetTextToRender("OFF");
						break;
					default:
						break;
					}
				}
			}
		}
		break;
		case VK_OEM_3:
			/*~ Key for US Keyboard*/
			mDebugMenu->isActive = !mDebugMenu->isActive;
			break;
		case VK_LEFT:
		{
			if (isActive && mDebugMenuAssociatedObjectList[currentlySelected].mType == Slider
				&& mDebugMenuAssociatedObjectList[currentlySelected].mData.sliderData.currentStep > 0)
			{
				mDebugMenuAssociatedObjectList[currentlySelected].mData.sliderData.currentStep--;
				Math::Vector3 tempScale = mDebugMenuAssociatedObjectList[currentlySelected].mAssociatedObject->getScale();
				tempScale -= Math::Vector3(mDebugMenuAssociatedObjectList[currentlySelected].mData.sliderData.delta);
				mDebugMenuAssociatedObjectList[currentlySelected].mAssociatedObject->setScale(
					tempScale.x, tempScale.y, tempScale.z);
				int tempCurrentStep = mDebugMenuAssociatedObjectList[currentlySelected].mData.sliderData.currentStep;
				int maxStep = mDebugMenuAssociatedObjectList[currentlySelected].mData.sliderData.maxStep;
				std::string textToRender;
				for (int i = 0; i < tempCurrentStep; i++)
					textToRender += "#";
				for (int i = 0; i < (maxStep - tempCurrentStep); i++)
					textToRender += ".";
				mDebugMenuAssociatedObjectList[currentlySelected].mUIElement->SetTextToRender(textToRender);
			}
		}
		break;
		case VK_RIGHT:
		{
			if (isActive && mDebugMenu->isActive && mDebugMenuAssociatedObjectList[currentlySelected].mType == Slider
				 && mDebugMenuAssociatedObjectList[currentlySelected].mData.sliderData.currentStep > 
				mDebugMenuAssociatedObjectList[currentlySelected].mData.sliderData.maxStep)
			{
				mDebugMenuAssociatedObjectList[currentlySelected].mData.sliderData.currentStep++;
				Math::Vector3 tempScale = mDebugMenuAssociatedObjectList[currentlySelected].mAssociatedObject->getScale();
				tempScale += Math::Vector3(mDebugMenuAssociatedObjectList[currentlySelected].mData.sliderData.delta);
				mDebugMenuAssociatedObjectList[currentlySelected].mAssociatedObject->setScale(
					tempScale.x, tempScale.y, tempScale.z);

				int tempCurrentStep = mDebugMenuAssociatedObjectList[currentlySelected].mData.sliderData.currentStep;
				int maxStep = mDebugMenuAssociatedObjectList[currentlySelected].mData.sliderData.maxStep;
				std::string textToRender;
				for (int i = 0; i < tempCurrentStep; i++)
					textToRender += "#";
				for (int i = 0; i < (maxStep - tempCurrentStep); i++)
					textToRender += ".";
				mDebugMenuAssociatedObjectList[currentlySelected].mUIElement->SetTextToRender(textToRender);
			}
		}
		break;
		case VK_UP:
		{
			if (isActive && currentlySelected > 0)
			{
				currentlySelected--;
				mDebugMenuAssociatedObjectList[currentlySelected].mAssociatedObject->SetVertexColor(0.0f, 1.0f, 0.0f, 1.0f);
			}
		}
		break;
		case VK_DOWN:
		{
			if (isActive && currentlySelected < UIElementCount)
			{
				currentlySelected++;
				mDebugMenuAssociatedObjectList[currentlySelected].mAssociatedObject->SetVertexColor(0.0f, 1.0f, 0.0f, 1.0f);
			}
		}
		break;
		}
	}
}

void Engine::Debug::DebugMenu::CreateButton(std::string buttonName,
	SharedPointer<Object> associatedObject)
{
	mDebugMenu->UIElementCount++;
	SharedPointer<Graphics::Text> tempUIElementName =
		Graphics::Text::CreateText("Game/textEffect.effect",
			"arial.ttf", mTransform);
	tempUIElementName->SetTextToRender(buttonName);
	tempUIElementName->SetVertexColor(0.0f, 1.0f, 0.0f, 0.5f);	
	
	Math::Vector3 tempPosition = mTransform.getPosition();
	tempPosition.x += 50.0f;
	mTransform.setPosition(tempPosition);

	SharedPointer<Graphics::Text> tempUIElement =
		Graphics::Text::CreateText("Game/textEffect.effect",
			"arial.ttf", mTransform);
	tempUIElement->SetTextToRender("OFF");
	tempUIElement->SetVertexColor(0.0f, 1.0f, 0.0f, 0.5f);
	
	tempPosition.y += 20.0f;
	mTransform.setPosition(tempPosition);
	
	UIElement tempElement;
	tempElement.mType = Button;
	tempElement.mData.buttonStatus = false;
	tempElement.mAssociatedObject = associatedObject;
	tempElement.mUIElementName = tempUIElementName;
	tempElement.mUIElement = tempUIElement;
	mDebugMenuAssociatedObjectList[mDebugMenu->UIElementCount] = tempElement;
}


void Engine::Debug::DebugMenu::CreateCheckBox(std::string iCheckBoxName,
	SharedPointer<Object> associatedObject)
{
	mDebugMenu->UIElementCount++;
	SharedPointer<Graphics::Text> tempUIElementName =
		Graphics::Text::CreateText("Game/textEffect.effect",
			"arial.ttf", mTransform);
	tempUIElementName->SetTextToRender(iCheckBoxName);
	tempUIElementName->SetVertexColor(0.0f, 1.0f, 0.0f, 0.5f);	

	Math::Vector3 tempPosition = mTransform.getPosition();
	tempPosition.x += 50.0f;
	mTransform.setPosition(tempPosition);

	SharedPointer<Graphics::Text> tempUIElement =
		Graphics::Text::CreateText("Game/textEffect.effect",
			"arial.ttf", mTransform);
	tempUIElement->SetTextToRender("[ ]");
	tempUIElement->SetVertexColor(0.0f, 1.0f, 0.0f, 0.5f);	
	tempPosition.y += 20.0f;
	mTransform.setPosition(tempPosition);

	UIElement tempElement;
	tempElement.mType = CheckBox;
	tempElement.mData.checkBoxStatus = false;
	tempElement.mUIElementName = tempUIElementName;
	tempElement.mUIElement = tempUIElement;
	tempElement.mAssociatedObject = associatedObject;
	mDebugMenuAssociatedObjectList[mDebugMenu->UIElementCount] = tempElement;
}


void Engine::Debug::DebugMenu::CreateSlider(std::string iSliderName,
	SharedPointer<Object> associatedObject,
	float min,
	float max)
{
	mDebugMenu->UIElementCount++;
	SharedPointer<Graphics::Text> tempUIElementName =
		Graphics::Text::CreateText("Game/textEffect.effect",
			"arial.ttf", mTransform);
	tempUIElementName->SetTextToRender(iSliderName);
	tempUIElementName->SetVertexColor(0.0f, 1.0f, 0.0f, 0.5f);
	
	Math::Vector3 tempPosition = mTransform.getPosition();
	tempPosition.x += 50.0f;
	mTransform.setPosition(tempPosition);

	SharedPointer<Graphics::Text> tempUIElement =
		Graphics::Text::CreateText("Game/textEffect.effect",
			"arial.ttf", mTransform);
	tempUIElement->SetTextToRender("[....................]");
	tempUIElement->SetVertexColor(0.0f, 1.0f, 0.0f, 0.5f);
	tempPosition.y += 20.0f;
	mTransform.setPosition(tempPosition);

	UIElement tempElement;
	tempElement.mType = Slider;
	tempElement.mData.sliderData.minVal = min;
	tempElement.mData.sliderData.maxVal = max;
	tempElement.mData.sliderData.initialVal = 1.0f;
	tempElement.mData.sliderData.currentStep = 0;
	tempElement.mData.sliderData.maxStep = 20;
	tempElement.mData.sliderData.delta = (max - min) / 20;
	tempElement.mUIElementName = tempUIElementName;
	tempElement.mUIElement = tempUIElement;
	tempElement.mAssociatedObject = associatedObject;
	mDebugMenuAssociatedObjectList[mDebugMenu->UIElementCount] = tempElement;
}


void Engine::Debug::DebugMenu::CreateText(std::string textName,
	std::string iText,
	SharedPointer<Object> associatedObject)
{
	mDebugMenu->UIElementCount++;
	SharedPointer<Graphics::Text> tempUIElementName =
		Graphics::Text::CreateText("Game/textEffect.effect",
			"arial.ttf", mTransform);
	tempUIElementName->SetTextToRender(textName);
	tempUIElementName->SetVertexColor(0.0f, 1.0f, 0.0f, 0.5f);	

	Math::Vector3 tempPosition = mTransform.getPosition();
	tempPosition.x += 50.0f;
	mTransform.setPosition(tempPosition);

	SharedPointer<Graphics::Text> tempUIElement =
		Graphics::Text::CreateText("Game/textEffect.effect",
			"arial.ttf", mTransform);
	tempUIElement->SetTextToRender(iText);
	tempUIElement->SetVertexColor(0.0f, 1.0f, 0.0f, 0.5f);	
	tempPosition.y += 20.0f;
	mTransform.setPosition(tempPosition);

	UIElement tempElement;
	tempElement.mType = Text;
	tempElement.mData.textString = iText;
	tempElement.mUIElementName = tempUIElementName;
	tempElement.mUIElement = tempUIElement;
	tempElement.mAssociatedObject = associatedObject;
	mDebugMenuAssociatedObjectList[mDebugMenu->UIElementCount] = tempElement;
}


Engine::Debug::DebugMenu::DebugMenu()
{
	UIElementCount = 0;
	isActive = false;
	currentlySelected = 0;
	mTransform.setPosition(Math::Vector3(EngineCore::getWindowingSystem()->getWindowWidth()-10.0f, 
		EngineCore::getWindowingSystem()->getWindowWidth() -10.0f, 0.0f));
	mTransform.setOrientation(Math::Quaternion::getIdentityQuartenion());
}


Engine::SharedPointer<Engine::Debug::DebugMenu> Engine::Debug::DebugMenu::GetDebugMenu()
{
	if(!mDebugMenu.isNull())
	{
		SharedPointer<DebugMenu> tempDebugMenu =
			SharedPointer<DebugMenu>(new DebugMenu(), "Engine::DebugMenu");

		mDebugMenu = tempDebugMenu;
		utils::StringHash temp = Engine::utils::StringHash(
			Engine::EngineCore::getStringPool()->findString("DebugMenuHandler"));

		EngineCore::getMessagingSystem()->addMessageHandler(temp, 
			mDebugMenu.CastSharedPointer<IMessageHandler>(),
			Engine::typedefs::HIGH);
	}
	return mDebugMenu;
}


bool Engine::Debug::DebugMenu::isActivated() const
{
	return isActive;
}


bool Engine::Debug::DebugMenu::isExist() const
{
	return mDebugMenuAssociatedObjectList.size() > 0 ? true : false;
}











