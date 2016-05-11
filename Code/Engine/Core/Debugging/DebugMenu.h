
#include <vector>
#include "../../Graphics/Text.h"
#ifdef _DEBUG
#ifndef __DEBUG_MENU_H
#define __DEBUG_MENU_H

#include "../Utilities/IMessageHandler.h"
#include "../Utilities/SharedPointer.h"
#include <map>

namespace Engine {
	class Object;
}

namespace Engine
{
	namespace Debug
	{
		enum UIElementType
		{
			Slider,
			CheckBox,
			Button,
			Text
		};

		class DebugMenu: public IMessageHandler
		{
		public:			
			static SharedPointer<DebugMenu> GetDebugMenu();			
			void CreateSlider(std::string iSliderName, 
				SharedPointer<Object> associatedObject,
				float min, 
				float max);
			void CreateCheckBox(std::string iCheckBoxName, 
				SharedPointer<Object> associatedObject);
			void CreateText(std::string textName, std::string text,
				SharedPointer<Object> associatedObject);
			void CreateButton(std::string buttonName, 
				SharedPointer<Object> associatedObject);
			bool isActivated() const;
			bool isExist() const;

			//IMessageHandler functions
			void HandleMessage(Engine::utils::StringHash &, 
				SharedPointer<RTTI> i_MessageSender, 
				void* i_pMessageData) override;
			std::string getTypeInfo() const override { return ""; }
			bool isBothSameType(SharedPointer<RTTI>, std::string) const override
			{ return true; }
		private:
			struct SliderData
			{
				float minVal;
				float maxVal;
				float initialVal;
				unsigned int currentStep;
				unsigned int maxStep;
				float delta;

				SliderData() = default;
				SliderData(SliderData &) = default;
				SliderData& operator=(SliderData&) = default;
			};

			union UIElementData
			{
				SliderData sliderData;
				bool buttonStatus;
				bool checkBoxStatus;
				std::string textString;

				UIElementData()
				{
					SliderData tempData = SliderData();
					sliderData = tempData;
					buttonStatus = false;
					checkBoxStatus = false;
					textString = "";
				}

				UIElementData& operator=(UIElementData&)
				{
					UIElementData tempUIElementData;
					tempUIElementData.
				}
				~UIElementData(){}
			};

			struct UIElement
			{
				UIElementType mType;
				SharedPointer<Object> mAssociatedObject;
				UIElementData mData;
				SharedPointer<Graphics::Text> mUIElementName;
				SharedPointer<Graphics::Text> mUIElement;

				UIElement()	{}
				~UIElement(){}
				UIElement(UIElement &) = default;
				UIElement& operator=(UIElement& iElement)
				{
					UIElement tempElement;
					tempElement.mType = iElement.mType;
					tempElement.mAssociatedObject =
						iElement.mAssociatedObject;
					tempElement.mData = iElement.mData;
					tempElement.mUIElementName =
						iElement.mUIElementName;
					tempElement.mUIElement =
						iElement.mUIElement;
					return tempElement;
				}
			};

			static SharedPointer<DebugMenu> mDebugMenu;
			uint16_t UIElementCount;
			uint16_t currentlySelected;
			bool isActive;
			std::map<int, UIElement> mDebugMenuAssociatedObjectList;
			Math::Transform mTransform;			
			DebugMenu();					
		};
	}
}

#endif
#endif