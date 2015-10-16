#ifndef __SCENE_H
#define __SCENE_H

#include "GameObject.h"
#include "../../../Core/Utilities/SharedPointer.h"
#include <vector>
#include "../../../Core/Time/FrameTime.h"

namespace Engine
{
	class Scene
	{
	public:
		static SharedPointer<Scene> CreateNewScene(std::string);
		bool addToScene(SharedPointer<GameObject>&);
		void drawScene();
		static SharedPointer<Engine::Scene> getScene(std::string);
		void renderScene(bool);
		static Engine::SharedPointer<Scene> getRenderableScene();
		static void deleteAllScene();
		~Scene();
	private:
		Scene(std::string);
		static bool isSceneExist(std::string);
		std::vector<SharedPointer<Engine::GameObject>> mScene;
		static std::map<std::string, SharedPointer<Scene>> mSceneList;
		static void deactivateAllSceneToRender();
		SharedPointer<Engine::Time::FrameTime> mTimer;
		std::string sceneName;
		bool render;
	};
}

#endif