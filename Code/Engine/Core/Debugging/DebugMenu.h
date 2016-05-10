#ifdef _DEBUG
#ifndef __DEBUG_MENU_H
#define __DEBUG_MENU_H
#include <string>

namespace Engine
{
	namespace Debug
	{
		class DebugMenu
		{
			static void CreateSlider(std::string iSliderName, float value, float min, float max);
			static void CreateCheckBox(std::string iCheckBoxName, bool value);
			static void CreateText(std::string textName, std::string textValue);
			static void CreateButton(std::string buttonName, void(*callBackFunc)(void*), void * param);
		};
	}
}

#endif
#endif