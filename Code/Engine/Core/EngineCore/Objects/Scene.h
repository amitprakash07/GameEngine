#ifndef __SCENE_H
#define __SCENE_H

#include "MeshObject.h"
#include "Camera.h"
#include "../../../Graphics/Line.h"
#include "../../../Graphics/Sprite.h"
#include "../../../Core/Utilities/SharedPointer.h"
#include <vector>
#include "../../../Core/Time/FrameTime.h"
#include "../../../Graphics/ReflectingObject.h"



namespace Engine
{	
	class Scene :public Object, IMessageHandler
	{
	public:
		static SharedPointer<Scene> CreateNewScene(std::string);
		static SharedPointer<Engine::Time::FrameTime> getTimer();
		static Engine::SharedPointer<Scene> getRenderableScene();
		template<typename T>
		bool addObjectToScene(SharedPointer<T>&);
		bool addCameraToScene(SharedPointer<Camera>&);
		void useCamera(const std::string) const;
		void useCamera(SharedPointer<Camera>) const;
		void drawScene(bool withDebug = true);
		void updateScene();
		static SharedPointer<Engine::Scene> getScene(std::string);
		void renderScene(bool);
		std::vector<SharedPointer<Engine::MeshObject>> getMeshObjectList() const;
		std::vector<SharedPointer<Engine::Graphics::Sprite>> getSpriteObjectList() const;
		std::vector<SharedPointer<Engine::Graphics::Line>> getLineList() const;
		std::vector<SharedPointer<Engine::Graphics::ReflectingObject>> getReflectingObjectList() const;
		SharedPointer<Camera> getActiveCamera() const;
		static void deleteAllScene();
		std::string getTypeInfo() const override { return ""; }
		bool isBothSameType(RTTI*, std::string) const override { return true; }
		static void applyPaintersAlgorithmForTransparency();
		static void sortAllReflectingObjects();
		//Object Override functions
		Math::Transform getTransform() override { return Math::Transform(); }
		void draw(bool) override {}
		bool isRenderable()const override { return true; }
		bool isDebugObject()const override { return false; }
		void updateObject() override;
		void setObjectController(IObjectController * iObjectController) override;
		void setTransform(Engine::Math::Vector3,
			Engine::Math::Quaternion = Engine::Math::Quaternion())override {}
		void resetTransform() override {}
		//IMesageHandler override function
		void HandleMessage(Engine::utils::StringHash &, RTTI* i_MessageSender, void* i_pMessageData) override;
		~Scene();
	private:
		static std::map<std::string, SharedPointer<Scene>> mSceneList;
		Scene(std::string);
		static bool isSceneExist(std::string);
		std::vector<SharedPointer<Engine::MeshObject>> mMeshObjectInSceneList;
		std::vector<SharedPointer<Engine::Graphics::Line>> mLineListInScene;
		std::vector<SharedPointer<Engine::Graphics::Sprite>> mSpriteListInScene;
		std::vector<SharedPointer<Engine::Graphics::ReflectingObject>> mReflectingObjectList;
		std::map<std::string, SharedPointer<Camera>> mCameraListInScene;
		static void deactivateAllSceneToRender();
		void deactivateAllCamera() const;
		SharedPointer<Engine::Time::FrameTime> mTimer;
		SharedPointer<Camera> activeCamera;
		
		static bool sortMeshObject(SharedPointer<MeshObject>,
			SharedPointer<MeshObject>);

		static bool sortSprites(SharedPointer<Engine::Graphics::Sprite>,
			SharedPointer<Engine::Graphics::Sprite>);

		static bool sortReflectingObject(SharedPointer<Engine::Graphics::ReflectingObject>,
			SharedPointer<Engine::Graphics::ReflectingObject>);
		
		SharedPointer<Camera> findCamera(const std::string) const;
		bool findCamera(const SharedPointer<Camera>) const;
		std::string sceneName;
		bool render;
		bool renderDebug;
		IObjectController * mObjectController;
	};
}

#endif