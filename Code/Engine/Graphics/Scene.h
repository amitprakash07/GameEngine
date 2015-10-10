#ifndef __SCENE_H
#define __SCENE_H

#include <vector>
#include <string>
#include "Mesh.h"
#include "Effects.h"

namespace Engine
{
	namespace Graphics
	{
		class Scene
		{
		public:
			static bool addToScene(std::string);
			static void drawScene();
			static void deleteScene();
			Scene();
			~Scene();
		private:
			static std::vector<Mesh*> scene;
		};
	}
}

#endif
