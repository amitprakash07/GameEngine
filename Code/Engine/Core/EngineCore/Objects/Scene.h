#ifndef __SCENE_H
#define __SCENE_H

#include "MeshObject.h"
#include "Camera.h"
#include "../../../Core/Utilities/SharedPointer.h"
#include <vector>
#include "../../../Core/Time/FrameTime.h"

namespace Engine
{
	class Scene :public RTTI
	{
	public:
		static SharedPointer<Scene> CreateNewScene(std::string);
		static SharedPointer<Engine::Time::FrameTime> getTimer();
		bool addGameObjectToScene(SharedPointer<MeshObject>&);
		bool addCameraToScene(SharedPointer<Camera>&);
		void useCamera(const std::string) const;
		void useCamera(SharedPointer<Camera>) const;
		void drawScene();
		static SharedPointer<Engine::Scene> getScene(std::string);
		void renderScene(bool);
		static Engine::SharedPointer<Scene> getRenderableScene();
		SharedPointer<Camera> getActiveCamera() const;
		static void deleteAllScene();
		std::string getTypeInfo() const override { return ""; }
		bool isBothSameType(RTTI*, std::string) const override { return true; }
		static void applyPaintersAlgorithmForTransparency();
		~Scene();
	private:
		static std::map<std::string, SharedPointer<Scene>> mSceneList;
		Scene(std::string);
		static bool isSceneExist(std::string);
		std::vector<SharedPointer<Engine::MeshObject>> mScene;
		std::map<std::string, SharedPointer<Camera>> mCameraListInScene;
		static void deactivateAllSceneToRender();
		void deactivateAllCamera() const;
		SharedPointer<Engine::Time::FrameTime> mTimer;
		SharedPointer<Camera> activeCamera;
		static bool sortingFunc(SharedPointer<MeshObject>,
			SharedPointer<MeshObject>);
		SharedPointer<Camera> findCamera(const std::string) const;
		bool findCamera(const SharedPointer<Camera>) const;
		std::string sceneName;
		bool render;
	};
}

#endif