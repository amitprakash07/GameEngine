#ifndef __UI_ELEMENT_H
#define __UI_ELEMENT_H

#include "../Core/Utilities/SharedPointer.h"
#include "../Graphics/Text.h"
#include "../../Engine/Core/EngineCore/Objects/MeshObject.h"

namespace Engine
{
	namespace UI
	{
		enum UIElementType
		{
			Slider,
			CheckBox,
			Button,
			Text
		};

		class UIElement
		{
		public:
			static SharedPointer<UIElement> CreateUIElement(
				UIElementType iType,
				SharedPointer<MeshObject> iAssociatedObject,
				SharedPointer<Graphics::Text> i_UIElementName,
				SharedPointer<Graphics::Text> i_UIElement);	

			static SharedPointer<UIElement> CreateUIElement(
				UIElementType iType,
				SharedPointer<MeshObject> iAssociatedObject,
				SharedPointer<Graphics::Text> i_UIElementName,
				SharedPointer<Graphics::Text> i_UIElement,
				float iSliderMinVal,
				float iSliderMaxVal);

			static SharedPointer<UIElement> CreateUIElement(
				UIElementType iType,
				SharedPointer<MeshObject> iAssociatedObject,
				SharedPointer<Graphics::Text> i_UIElementName,
				SharedPointer<Graphics::Text> i_UIElement,
				std::string textText);

			SharedPointer<MeshObject> GetAssociatedObject() const;
			SharedPointer<Graphics::Text> GetUIElementName() const;
			SharedPointer<Graphics::Text> GetUIElement() const;
			void SetSliderMaxValue(float iMax);
			void SetSliderMinValue(float iMin);
			void SetSliderCurrentStep(uint8_t iCurrentStep);
			void SetSliderMaxStep(uint8_t iMaxStep);
			void SetCheckBoxStatus(bool iRequest);
			void SetButtonStatus(bool iRequest);
			void SetUIType(UIElementType iType);
			void SetTextForTextUI(std::string iText);

			float GetSliderMaxValue() const;
			float GetSliderMinValue() const;
			uint8_t GetSliderCurrentStep() const;
			uint8_t GetSliderMaxStep() const;
			bool GetCheckBoxStatus() const;
			bool GetButtonStatus() const;
			UIElementType GetUIType() const;
			std::string GetTextForTextUI() const;
		private:
			UIElementType mType;
			SharedPointer<Engine::MeshObject> mAssociatedObject;
			SharedPointer<Graphics::Text> mUIElementName;
			SharedPointer<Graphics::Text> mUIElement;
			std::string textForTextType;
			float sliderMaxVal;
			float sliderMinVal;
			uint16_t sliderCurrentStep;
			uint16_t  sliderMaxStep;
			bool buttonStatus;
			bool checkBoxStatus;			
			UIElement(UIElementType iType,
				SharedPointer<MeshObject> iAssociatedObject,
				SharedPointer<Graphics::Text> i_UIElementName,
				SharedPointer<Graphics::Text> i_UIElement);
		};
	}
}

#endif