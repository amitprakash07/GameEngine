//#include "Slider.h"
//
//
//Engine::SharedPointer<Engine::UI::Slider> Engine::UI::Slider::CreateSlider(
//	std::string iName, 
//	float* value, 
//	float iMax, 
//	float iMin,
//	Math::Transform iTransform)
//{
//	SharedPointer<Slider> tempSlider =
//		SharedPointer<Slider>(new Slider(), "Engine::UI::Slider");
//	SharedPointer<Graphics::Text> tempNameText =
//		Engine::Graphics::Text::CreateText("Game/textEffect.effect", "arial.ttf",
//			iTransform);
//	tempNameText->SetTextToRender(iName);
//
//	tempNameText->SetVertexColor(0.0f, 1.0f, 0.0f, 1.0f);
//	SharedPointer<Graphics::Text> tempTextSlider = 
//		Engine::Graphics::Text::CreateText("Game/textEffect.effect", "arial.ttf",
//			Engine::Math::Transform());
//	tempTextSlider->SetVertexColor(0.0f, 1.0f, 0.0f, 1.0f);
//
//
//	tempSlider->mName = tempNameText;
//	tempSlider->mTextSlider = tempTextSlider;
//	tempSlider->max = iMax;
//	tempSlider->min = iMin;
//
//}
//
//
//Engine::Graphics::RGBAColor Engine::UI::Slider::GetVertexColor() const
//{
//	return mName->GetVertexColor();
//}
//
//
//void Engine::UI::Slider::HandleMessage(Engine::utils::StringHash&, SharedPointer<RTTI> i_MessageSender, void* i_pMessageData)
//{
//	
//}
//
//
//void Engine::UI::Slider::SetVertexColor(float iR, float iG, float iB, float iA)
//{
//	
//}
//
//Engine::UI::Slider::Slider()
//{
//	
//}
//
//
//void Engine::UI::Slider::draw(bool)
//{
//	
//}
//
//
//Engine::Math::Vector3 Engine::UI::Slider::getScale() const
//{
//	
//}
//
//
//Engine::Math::Transform Engine::UI::Slider::getTransform()
//{
//	
//}
//
//
//void Engine::UI::Slider::resetTransform()
//{
//	
//}
//
//void Engine::UI::Slider::setObjectController(IObjectController* objectController)
//{
//	
//}
//
//
//void Engine::UI::Slider::setScale(float x, float y, float z)
//{
//	
//}
//
//
//void Engine::UI::Slider::updateObject()
//{
//	
//}
//
//
//void Engine::UI::Slider::setTransform(Engine::Math::Vector3, Engine::Math::Quaternion)
//{
//	
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
