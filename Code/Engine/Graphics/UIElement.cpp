#include "UIElement.h"

Engine::SharedPointer<Engine::UI::UIElement> Engine::UI::UIElement::CreateUIElement(
	UIElementType iType, 
	SharedPointer<MeshObject> iAssociatedObject, 
	SharedPointer<Graphics::Text> i_UIElementName, 
	SharedPointer<Graphics::Text> i_UIElement)
{
	SharedPointer<UIElement>	 tempUIElement =
		SharedPointer<UIElement>(new UIElement(
		iType, iAssociatedObject, i_UIElementName, i_UIElement), "Engine::UI::Element");
	return tempUIElement;
}



Engine::SharedPointer<Engine::UI::UIElement> Engine::UI::UIElement::CreateUIElement(
	UIElementType iType,
	SharedPointer<MeshObject> iAssociatedObject,
	SharedPointer<Graphics::Text> i_UIElementName,
	SharedPointer<Graphics::Text> i_UIElement, 
	float iSliderMinVal,
	float iSliderMaxVal)
{
	SharedPointer<UIElement>	 tempUIElement =
		SharedPointer<UIElement>(new UIElement(
			iType, iAssociatedObject, i_UIElementName, i_UIElement), "Engine::UI::Element");
	tempUIElement->sliderMinVal = iSliderMinVal;
	tempUIElement->sliderMaxVal = iSliderMaxVal;
	return tempUIElement;
}



Engine::SharedPointer<Engine::UI::UIElement> Engine::UI::UIElement::CreateUIElement(
	UIElementType iType,
	SharedPointer<MeshObject> iAssociatedObject,
	SharedPointer<Graphics::Text> i_UIElementName,
	SharedPointer<Graphics::Text> i_UIElement,
	std::string textText)
{
	SharedPointer<UIElement>	 tempUIElement =
		SharedPointer<UIElement>(new UIElement(
			iType, iAssociatedObject, i_UIElementName, i_UIElement), "Engine::UI::Element");
	tempUIElement->textForTextType = textText;
	return tempUIElement;
}


Engine::SharedPointer<Engine::MeshObject> Engine::UI::UIElement::GetAssociatedObject() const
{
	return mAssociatedObject;
}


bool Engine::UI::UIElement::GetButtonStatus() const
{
	return  buttonStatus;
}


bool Engine::UI::UIElement::GetCheckBoxStatus() const
{
	return checkBoxStatus;
}



uint8_t Engine::UI::UIElement::GetSliderCurrentStep() const
{
	return sliderCurrentStep;
}


uint8_t Engine::UI::UIElement::GetSliderMaxStep() const
{
	return sliderMaxStep;
}



float Engine::UI::UIElement::GetSliderMaxValue() const
{
	return sliderMaxVal;
}


float Engine::UI::UIElement::GetSliderMinValue() const
{
	return sliderMinVal;
}


Engine::SharedPointer<Engine::Graphics::Text> Engine::UI::UIElement::GetUIElement() const
{
	return mUIElement;
}


Engine::SharedPointer<Engine::Graphics::Text> Engine::UI::UIElement::GetUIElementName() const
{
	return mUIElementName;
}


void Engine::UI::UIElement::SetButtonStatus(bool iRequest)
{
	buttonStatus = iRequest;
}


void Engine::UI::UIElement::SetCheckBoxStatus(bool iRequest)
{
	checkBoxStatus = iRequest;
}


void Engine::UI::UIElement::SetSliderCurrentStep(uint8_t iCurrentStep)
{
	sliderCurrentStep = iCurrentStep;
}


void Engine::UI::UIElement::SetSliderMaxStep(uint8_t iMaxStep)
{
	sliderMaxStep = iMaxStep;
}


void Engine::UI::UIElement::SetSliderMaxValue(float iMax)
{
	sliderMaxVal = iMax;
}



void Engine::UI::UIElement::SetSliderMinValue(float iMin)
{
	sliderMinVal = iMin;
}


std::string Engine::UI::UIElement::GetTextForTextUI() const
{
	return textForTextType;
}

Engine::UI::UIElementType Engine::UI::UIElement::GetUIType() const
{
	return mType;
}


void Engine::UI::UIElement::SetTextForTextUI(std::string iText)
{
	textForTextType = iText;
}


void Engine::UI::UIElement::SetUIType(UIElementType iType)
{
	mType = iType;
}

Engine::UI::UIElement::UIElement(UIElementType iType,
	SharedPointer<MeshObject> iAssociatedObject,
	SharedPointer<Graphics::Text> i_UIElementName,
	SharedPointer<Graphics::Text> i_UIElement)
{
	mType = iType;
	mAssociatedObject = iAssociatedObject;
	mUIElementName = i_UIElementName;
	mUIElement = i_UIElement;
	sliderMaxVal = 0.0f;
	sliderMinVal = 0.0f;
	sliderCurrentStep = 1;
	sliderMaxStep = 1;
	buttonStatus = false;
	checkBoxStatus = false;	
}

















