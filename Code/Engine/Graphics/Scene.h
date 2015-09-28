#ifndef __SCENE_H
#define __SCENE_H

#include <vector>
#include <string>
#include "Mesh.h"

namespace Engine
{
	namespace Graphics
	{
		class Scene
		{
		public:
			static bool addToScene(std::string);
			static void drawScene();
			Scene();
			~Scene();
		private:
			static std::vector<Mesh*> scene;

		};
	}
}

#endif
