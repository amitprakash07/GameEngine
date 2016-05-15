#include "DebugMenuController.h"
#include "../../../Engine/Windows/WindowsFunctions.h"
#include "../../../Engine/Core/Debugging/DebugMenu.h"
#include "../../../Engine/Core/EngineCore/Objects/Scene.h"
#include "../../../Engine/Core/Physics/PhysicsSystem.h"


void Game::DebugMenuController::updateObject(Engine::Object& iObject,
	Engine::typedefs::ActionWithKeyBound iAction)
{	
	Engine::SharedPointer<Engine::Debug::DebugMenu> currentDebugMenu =
		Engine::Debug::DebugMenu::GetDebugMenu();

	bool scenInfo = Engine::Scene::getRenderableScene()->IsNewFrame();

	if (!currentDebugMenu.isNull() && Engine::Scene::getRenderableScene()->IsNewFrame())
	{
		std::map<int, Engine::SharedPointer<Engine::UI::UIElement>> mDebugMenuAssociatedObjectList
			= currentDebugMenu->GetDebugObjects();
		uint8_t currentlySelected = currentDebugMenu->GetCurrentSelectionIndex();

		switch (iAction.keyVal)
		{
		case VK_SPACE:
		{
			if (currentDebugMenu->isActivated())
			{				
				Engine::UI::UIElementType currentType = mDebugMenuAssociatedObjectList[currentlySelected]->GetUIType();
				if ((currentType == Engine::UI::CheckBox || currentType == Engine::UI::Button))
				{
					switch (currentType)
					{
					case Engine::UI::CheckBox:
					{
						bool currentStatus = mDebugMenuAssociatedObjectList[currentlySelected]->GetCheckBoxStatus();
						mDebugMenuAssociatedObjectList[currentlySelected]->SetCheckBoxStatus(!currentStatus);
						Engine::SharedPointer<Engine::MeshObject> tempMeshObject =
							mDebugMenuAssociatedObjectList[currentlySelected]->GetAssociatedObject();

						switch (!currentStatus)
						{
						case true:
						{
							Engine::Physics::PhysicsSystem::GetPhysicsSystem()->SetShowCollisionMesh(true);
							mDebugMenuAssociatedObjectList[currentlySelected]->GetUIElement()->SetTextToRender("[X]");							
							/*tempMeshObject->SetVertexColor(1.0f, 0.0f, 0.0f, 1.0f);
							tempMeshObject->setRenderable(true);*/
						}
						break;
						case false:
						{
							Engine::Physics::PhysicsSystem::GetPhysicsSystem()->SetShowCollisionMesh(false);
							mDebugMenuAssociatedObjectList[currentlySelected]->GetUIElement()->SetTextToRender("[ ]");
							//tempMeshObject->setRenderable(false);
						}
						break;
						}
					}
					break;

					case Engine::UI::Button:
					{
						bool currentStatus = mDebugMenuAssociatedObjectList[currentlySelected]->GetButtonStatus();
						mDebugMenuAssociatedObjectList[currentlySelected]->SetButtonStatus(!currentStatus);
						Engine::SharedPointer<Engine::MeshObject> tempMeshObject =
							mDebugMenuAssociatedObjectList[currentlySelected]->GetAssociatedObject();

						switch(!currentStatus)
						{
						case true:
							mDebugMenuAssociatedObjectList[currentlySelected]->GetUIElement()->SetTextToRender("ON");
							tempMeshObject->setScale(1.0f, 1.0f, 1.0f);
							break;
						case false:
							mDebugMenuAssociatedObjectList[currentlySelected]->GetUIElement()->SetTextToRender("OFF");
							break;
						}						
					}
					break;
					default:
						break;
					}

				}
			}
			
		}
		break;	
		case 0x31:
		{
			if (currentDebugMenu->isActivated())
			{
				if(mDebugMenuAssociatedObjectList[currentlySelected]->GetCheckBoxStatus())
					Engine::Physics::PhysicsSystem::EnableCollisionDebugging(true);
				else
					Engine::Physics::PhysicsSystem::EnableCollisionDebugging(false);
			}
		}
		break;
		case VK_LEFT:
		{
			if (currentDebugMenu->isActivated() && mDebugMenuAssociatedObjectList[currentlySelected]->GetUIType() == Engine::UI::Slider
				&& mDebugMenuAssociatedObjectList[currentlySelected]->GetSliderCurrentStep() > 0)
			{
				mDebugMenuAssociatedObjectList[currentlySelected]->SetSliderCurrentStep(
					mDebugMenuAssociatedObjectList[currentlySelected]->GetSliderCurrentStep() - 1);

				Engine::Math::Vector3 tempScale = mDebugMenuAssociatedObjectList[currentlySelected]->GetAssociatedObject()->getScale();
				tempScale -= Engine::Math::Vector3(0.5, 0.5, 0.5);

				mDebugMenuAssociatedObjectList[currentlySelected]->GetAssociatedObject()->setScale(
					tempScale.x, tempScale.y, tempScale.z);
				int tempCurrentStep = mDebugMenuAssociatedObjectList[currentlySelected]->GetSliderCurrentStep();
				int maxStep = mDebugMenuAssociatedObjectList[currentlySelected]->GetSliderMaxStep();
				std::string textToRender;
				for (int i = 0; i < tempCurrentStep; i++)
					textToRender += "#";
				for (int i = 0; i < (maxStep - tempCurrentStep); i++)
					textToRender += "..";
				mDebugMenuAssociatedObjectList[currentlySelected]->GetUIElement()->SetTextToRender(textToRender);
			}
		}
		break;
		case VK_RIGHT:
		{
			if (currentDebugMenu->isActivated() && mDebugMenuAssociatedObjectList[currentlySelected]->GetUIType() == Engine::UI::Slider
				&& mDebugMenuAssociatedObjectList[currentlySelected]->GetSliderCurrentStep() <
				mDebugMenuAssociatedObjectList[currentlySelected]->GetSliderMaxStep())
			{
				mDebugMenuAssociatedObjectList[currentlySelected]->SetSliderCurrentStep(
					mDebugMenuAssociatedObjectList[currentlySelected]->GetSliderCurrentStep() + 1);

				Engine::Math::Vector3 tempScale = mDebugMenuAssociatedObjectList[currentlySelected]->GetAssociatedObject()->getScale();
				tempScale += Engine::Math::Vector3(0.5, 0.5, 0.5);
				mDebugMenuAssociatedObjectList[currentlySelected]->GetAssociatedObject()->setScale(
					tempScale.x, tempScale.y, tempScale.z);
				int tempCurrentStep = mDebugMenuAssociatedObjectList[currentlySelected]->GetSliderCurrentStep();
				int maxStep = mDebugMenuAssociatedObjectList[currentlySelected]->GetSliderMaxStep();
				std::string textToRender;
				textToRender = "[";
				for (int i = 0; i < tempCurrentStep; i++)
					textToRender += "#";
				for (int i = 0; i < (maxStep - tempCurrentStep); i++)
					textToRender += ".";
				textToRender += "]";
				mDebugMenuAssociatedObjectList[currentlySelected]->GetUIElement()->SetTextToRender(textToRender);
			}
		}
		break;
		case VK_UP:
		{
			if (currentDebugMenu->isActivated() && currentlySelected > 0 && currentlySelected < currentDebugMenu->GetElementCount())
			{
				currentlySelected--;
				currentDebugMenu->SetCurrentlySelected(currentlySelected);
				for (std::map<int, Engine::SharedPointer<Engine::UI::UIElement>>::iterator i = mDebugMenuAssociatedObjectList.begin();
					i != mDebugMenuAssociatedObjectList.end(); ++i)
				{
					i->second->GetUIElement()->SetVertexColor(0.0f, 1.0f, 0.0f, 0.5f);
					i->second->GetUIElementName()->SetVertexColor(0.0f, 1.0f, 0.0f, 0.5f);
				}
				mDebugMenuAssociatedObjectList[currentlySelected]->GetUIElement()->SetVertexColor(0.0f, 1.0f, 0.0f, 1.0f);
				mDebugMenuAssociatedObjectList[currentlySelected]->GetUIElementName()->SetVertexColor(0.0f, 1.0f, 0.0f, 1.0f);
			}
		}
		break;
		case VK_DOWN:
		{
			if (currentDebugMenu->isActivated() && currentlySelected < currentDebugMenu->GetElementCount() && currentlySelected >= 0)
			{
				currentlySelected++;
				currentDebugMenu->SetCurrentlySelected(currentlySelected);
				for (std::map<int, Engine::SharedPointer<Engine::UI::UIElement>>::iterator i = mDebugMenuAssociatedObjectList.begin();
					i != mDebugMenuAssociatedObjectList.end(); ++i)
				{
					i->second->GetUIElement()->SetVertexColor(0.0f, 1.0f, 0.0f, 0.5f);
					i->second->GetUIElementName()->SetVertexColor(0.0f, 1.0f, 0.0f, 0.5f);
				}
				mDebugMenuAssociatedObjectList[currentlySelected]->GetUIElement()->SetVertexColor(0.0f, 1.0f, 0.0f, 1.0f);
				mDebugMenuAssociatedObjectList[currentlySelected]->GetUIElementName()->SetVertexColor(0.0f, 1.0f, 0.0f, 1.0f);
			}
		}
		break;
		}		
	}
}

